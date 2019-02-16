#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "abb.h"
#include "pila.h"


typedef struct nodo{
	void* dato;
	char* clave;
	struct nodo* hijo_izq;
	struct nodo* hijo_der;
} nodo_t;

struct abb{
	nodo_t* raiz;
	abb_comparar_clave_t comparar_clave;
	abb_destruir_dato_t destruir_dato;
	size_t cantidad;
};

struct abb_iter{
    const abb_t* arbol;
    pila_t* visitados;
};

nodo_t* nodo_buscar(nodo_t* nodo, const abb_t* abb, const char* clave){

	if(!nodo) 
		return NULL;

	int comp = abb->comparar_clave(nodo->clave, clave);

	if(comp == 0)
		return nodo;

	if(comp > 0)
		return nodo_buscar(nodo->hijo_izq, abb, clave);

	return nodo_buscar(nodo->hijo_der, abb, clave);
}

nodo_t* padre_buscar(const abb_t* abb, const char* clave){

	nodo_t* padre = NULL;

	nodo_t* nodo = abb->raiz;

	int cmp = abb->comparar_clave(clave, nodo->clave);

	while(cmp){
		padre = nodo;
		if(cmp > 0)
			nodo = nodo->hijo_der;
		else
			nodo = nodo->hijo_izq;
		if(!nodo)
			return padre;
		cmp = abb->comparar_clave(clave, nodo->clave);
	}

	return padre;
}

void* abb_borrar(abb_t* arbol, const char* clave){
	
	if(!arbol || !arbol->raiz)
		return NULL;

	nodo_t* nodo = nodo_buscar(arbol->raiz, arbol, clave);
	
	if(!nodo)
		return NULL;

	nodo_t* padre = padre_buscar(arbol, nodo->clave);

	void* dato_aux = nodo->dato;

	if(!nodo->hijo_der && !nodo->hijo_izq){

		if(padre){
			if(padre->hijo_izq == nodo)
				padre->hijo_izq = NULL;
			
			else
				padre->hijo_der = NULL;
		}

		else
			arbol->raiz = NULL;

		dato_aux = nodo->dato;
		free(nodo->clave);
		nodo->clave = NULL;
	}
	else if(!nodo->hijo_der || !nodo->hijo_izq){
		dato_aux = nodo->dato;
		if(padre){
			if(padre->hijo_izq == nodo){
				if(nodo->hijo_izq)
					padre->hijo_izq = nodo->hijo_izq;
				else
					padre->hijo_izq = nodo->hijo_der;
			}
			else{
				if(nodo->hijo_izq)
					padre->hijo_der = nodo->hijo_izq;
				else
					padre->hijo_der = nodo->hijo_der;
			}
		}
		else{
			if(nodo->hijo_izq)
				arbol->raiz = nodo->hijo_izq;
			else
				arbol->raiz = nodo->hijo_der;
		}
		if(nodo && nodo->clave)
			free(nodo->clave);
	}
	else if(nodo->hijo_der && nodo->hijo_izq){

		dato_aux = nodo->dato;

		nodo_t* reemplazo = nodo->hijo_izq;
		nodo_t* padre_reemplazo = nodo;
		
		while(reemplazo->hijo_der){
			padre_reemplazo = reemplazo;
			reemplazo = reemplazo->hijo_der;
		}

		char* clave_aux = reemplazo->clave;

		void* dato_reemplazo = reemplazo->dato;

		free(nodo->clave);
		
		nodo->clave = clave_aux;
		nodo->dato = dato_reemplazo;

		if(padre_reemplazo->hijo_der == reemplazo)
			padre_reemplazo->hijo_der = reemplazo->hijo_izq;
		else
			padre_reemplazo->hijo_izq = reemplazo->hijo_izq;

		arbol->cantidad--;
		free(reemplazo);
		return dato_aux;
	}

	

	arbol->cantidad--;

	free(nodo);

	return dato_aux;
}


nodo_t* nodo_crear(const char* clave, void* dato){

	nodo_t* nodo = malloc(sizeof(nodo_t));

	if(!nodo)
		return NULL;

	char* clave_aux = malloc(sizeof(char)*(strlen(clave)+1));
    if (!clave_aux){
        free(nodo);
        return NULL;
    }

	nodo->dato = dato;
	strcpy(clave_aux, clave);
	nodo->clave = clave_aux;
	nodo->hijo_izq = NULL;
	nodo->hijo_der = NULL;

	return nodo;
}

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){

	abb_t* abb = malloc(sizeof(abb_t));

	if(!abb)
		return NULL;

	abb->raiz = NULL;
	abb->comparar_clave = cmp;
	abb->destruir_dato = destruir_dato;
	abb->cantidad = 0;

	return abb;

}


bool abb_pertenece(const abb_t *arbol, const char *clave){

	if(nodo_buscar(arbol->raiz, arbol, clave))
		return true;

	return false;
}

bool abb_guardar(abb_t *arbol, const char *clave, void *dato){

	nodo_t* nodo = nodo_crear(clave, dato);

	if(!nodo)
		return false;

	if(!arbol->raiz)
		arbol->raiz = nodo;

	else{
		nodo_t* buscado = nodo_buscar(arbol->raiz, arbol, clave);

		if(buscado){
			void* dato_aux = buscado->dato;
			buscado->dato = dato;
			if(arbol->destruir_dato)
				arbol->destruir_dato(dato_aux);			
			free(nodo->clave);
			free(nodo);
			return true;
		}
		else{
			nodo_t* padre;
			nodo_t* actual = arbol->raiz;

			int comp; 

			while(actual){

				comp = arbol->comparar_clave(actual->clave, clave);
			
				padre = actual;

				if(comp > 0)
					actual = actual->hijo_izq;
			
				if(comp < 0)
					actual = actual->hijo_der;
			}

			comp = arbol->comparar_clave(padre->clave, clave);

			if(comp < 0)
				padre->hijo_der = nodo;
			else	
				padre->hijo_izq = nodo;
		}
	}

	arbol->cantidad++;
	
	return true;
}

void* abb_obtener(const abb_t *arbol, const char *clave){

	nodo_t* nodo = nodo_buscar(arbol->raiz, arbol, clave);

	if(!nodo)
		return NULL;

	return nodo->dato;
}

size_t abb_cantidad(abb_t *arbol){
	
	return arbol->cantidad;
}


void _abb_destruir(nodo_t* nodo, abb_t* abb){

	if(!nodo) 
		return;

	_abb_destruir(nodo->hijo_izq, abb);
	_abb_destruir(nodo->hijo_der, abb);

	if(abb->destruir_dato)
		abb->destruir_dato(nodo->dato);

	free(nodo->clave);
	free(nodo);

}

void abb_destruir(abb_t *arbol){

	_abb_destruir(arbol->raiz, arbol);

	free(arbol);
}


//*************** ITERADOR EXTERNO ***************//

void apilar_nodos_izq (pila_t* visitados, nodo_t* nodo){

	while(nodo){
		pila_apilar(visitados, nodo);
		nodo = nodo->hijo_izq;
	}
}

abb_iter_t *abb_iter_in_crear(const abb_t *arbol){

	if(!arbol)
		return NULL;

	abb_iter_t* iter = malloc(sizeof(abb_iter_t));

	if(!iter)
		return NULL;

	iter->visitados = pila_crear();

	if(!iter->visitados){
		free(iter);
		return NULL;
	}

	apilar_nodos_izq(iter->visitados, arbol->raiz);

	iter->arbol = arbol;
	return iter;
}

bool abb_iter_in_al_final(const abb_iter_t *iter){

	return(pila_esta_vacia(iter->visitados));

}

bool abb_iter_in_avanzar(abb_iter_t *iter){

	if(abb_iter_in_al_final(iter))
		return false;

	nodo_t* ult = pila_desapilar(iter->visitados);
	apilar_nodos_izq(iter->visitados, ult->hijo_der);
	return true;
}

const char *abb_iter_in_ver_actual(const abb_iter_t *iter){

	if (abb_iter_in_al_final(iter))
        return NULL;

    nodo_t* actual = pila_ver_tope(iter->visitados);

    return(actual->clave);
}

void abb_iter_in_destruir(abb_iter_t* iter){

	pila_destruir(iter->visitados);
	free(iter);
}


//*************** ITERADOR INTERNO ***************//


bool _abb_in_order(nodo_t* nodo, bool visitar(const char *, void *, void*), void *extra){
    
    if(!nodo){
        return false;
    }

    if(nodo->hijo_izq){
        if(!_abb_in_order(nodo->hijo_izq, visitar, extra))
        	return false;
    }

    if(!visitar(nodo->clave, nodo->dato, extra)){
            return false;
        }

    if(nodo->hijo_der){
        if(_abb_in_order(nodo->hijo_der, visitar, extra))
        	return false;
    }

    return true;
}

void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra){

    if (!arbol){
        return;
    }

    _abb_in_order(arbol->raiz, visitar, extra);
}

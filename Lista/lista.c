#include "lista.h"

#include <stdlib.h>

struct nodo;
typedef struct nodo nodo_t;

struct nodo{

	void* dato;
	nodo_t* prox;
};

struct lista{

	nodo_t* prim;
	nodo_t* ult;
	size_t largo;
};

struct lista_iter{

	nodo_t *actual;
    nodo_t *anterior;
    lista_t* lista;
};


/*********LISTA*********/

lista_t *lista_crear(void){

	lista_t* lista = malloc(sizeof(lista_t));

	if(!lista)
		return(NULL);

	lista->prim = NULL;

	lista->ult = NULL;

	lista->largo = 0;

	return(lista);
}

bool lista_esta_vacia(const lista_t *lista){

	return(lista->prim == NULL);
}

bool lista_insertar_primero(lista_t *lista, void *dato){

	nodo_t* nodo = malloc(sizeof(nodo_t));

	if(!nodo)

		return(false);

	nodo->dato = dato;

	nodo->prox = NULL;

	if(!lista->prim){

		lista->prim = nodo;

		lista->ult = nodo;
	}

	else {

		nodo_t* aux = lista->prim;

		lista->prim = nodo;

		lista->prim->prox = aux;
	}

	lista->largo++;

	return(true);
}

bool lista_insertar_ultimo(lista_t *lista, void *dato){

	nodo_t* nodo = malloc(sizeof(nodo_t));

	if(!nodo)

		return(false);

	nodo->dato = dato;

	nodo->prox = NULL;

	if(!lista->prim)

		lista->prim = nodo;

	else

		lista->ult->prox = nodo;

	lista->ult = nodo;

	lista->largo++;

	return(true);
}

void *lista_borrar_primero(lista_t *lista) {

	nodo_t* aux;

	void* aux_dato;

	if(!lista->prim)
		return(NULL);

	aux = lista->prim;

	lista->prim = lista->prim->prox;

	aux_dato = aux->dato;

	lista->largo--;

	free(aux);

	return(aux_dato);
}

void *lista_ver_primero(const lista_t *lista){

	if(!lista->prim)
		return(NULL);

	return(lista->prim->dato);
}

void *lista_ver_ultimo(const lista_t* lista){

	if(!lista->prim)
		return(NULL);

	return(lista->ult->dato);
}

size_t lista_largo(const lista_t *lista){

	return(lista->largo);
}

void lista_destruir(lista_t *lista, void destruir_dato(void *)){

	while(!lista_esta_vacia(lista)){

		void* elem_borrado = lista_borrar_primero(lista);

		if(destruir_dato)
			destruir_dato(elem_borrado);
	}

	free(lista);
}

/*********ITERADOR EXTERNO*********/

lista_iter_t *lista_iter_crear(lista_t *lista){

	lista_iter_t* iter = malloc(sizeof(lista_iter_t));

	if(!iter)
		return(NULL);

	iter->lista = lista;

	iter->actual = lista->prim;

	iter->anterior = NULL;

	return(iter);
}

bool lista_iter_avanzar(lista_iter_t *iter){

	if(!iter->actual)
		return(false);

	iter->anterior = iter->actual;

	iter->actual = iter->actual->prox;

	return(true);
}

void *lista_iter_ver_actual(const lista_iter_t *iter){

	if(!iter->actual)
		return(NULL);

	return(iter->actual->dato);
}

bool lista_iter_al_final(const lista_iter_t *iter){

	return(iter->actual == NULL);
}

void lista_iter_destruir(lista_iter_t *iter){

	free(iter);
}

bool lista_iter_insertar(lista_iter_t *iter, void *dato){

	nodo_t* nodo = malloc(sizeof(nodo_t));

	if(!nodo)
		return(false);

	nodo->dato = dato;

	if(!iter->anterior){

		iter->lista->prim = nodo;
	}

	else{
		
		iter->anterior->prox = nodo;
	}

	nodo->prox = iter->actual;

	iter->actual = nodo;

	if(!iter->actual->prox)

		iter->lista->ult = iter->actual;

	iter->lista->largo++;

	return(true);
}

void *lista_iter_borrar(lista_iter_t *iter){

	nodo_t* aux;

	void* aux_dato;

	if(lista_esta_vacia(iter->lista) || lista_iter_al_final(iter))
		return(NULL);

	if(iter->actual == iter->lista->prim){

		aux_dato = lista_borrar_primero(iter->lista);

		iter->actual = iter->lista->prim;
	}

	else{

		aux = iter->actual;

		aux_dato = aux->dato;

		iter->anterior->prox = iter->actual->prox;

		iter->actual = iter->anterior->prox;

		if(aux == iter->lista->ult)
			iter->lista->ult = iter->anterior;

		iter->lista->largo--;
		
		free(aux);
	}

	return(aux_dato);
}


/*********ITERADOR INTERNO*********/

void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra){

	nodo_t* aux = lista->prim;

	bool aux_func;
	
	while(aux){

		aux_func = visitar(aux->dato, extra);

		if(!aux_func)
			return;

		aux = aux->prox;
	}
}
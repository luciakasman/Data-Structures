#include "pila.h"
#include <stdlib.h>
#include <stdio.h>
#define CAP_MINIMA 20
#define FACTOR_REDIMENSION 2
#define CRITERIO_REDIMENSION 4
#define AGRANDAR 1
#define ACHICAR 0

/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void** datos;
    size_t cantidad;  // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};
/* *****************************************************************
 *                    FUNCIONES AUXILIARES                  
 * ****************************************************************/
/*void** pila_agrandar(pila_t *pila){
	pila->datos = realloc(pila->datos, pila->capacidad * sizeof(void*) * 2);
	if(pila->datos != NULL){
		pila->capacidad *= 2;
		return pila->datos;
	}
	return NULL;
}
	
void** pila_achicar(pila_t *pila){
	if(pila->capacidad / 2 < CAP_MINIMA)
		return pila->datos;
	pila->datos = realloc(pila->datos, (pila->capacidad / 2) * sizeof(void*));
	if(pila->datos == NULL){
		return NULL;
	}
	pila->capacidad /= 2;
	return pila->datos;
}
*/

void** pila_redimensionar(pila_t *pila, int accion){
	if(accion){
		pila->datos = realloc(pila->datos, pila->capacidad * sizeof(void*) * FACTOR_REDIMENSION);
		if(pila->datos){
			pila->capacidad *= FACTOR_REDIMENSION;
			return pila->datos;
		}return NULL;
	}else{
		if(pila->capacidad / FACTOR_REDIMENSION < CAP_MINIMA)
			return pila->datos;
		pila->datos = realloc(pila->datos, (pila->capacidad / FACTOR_REDIMENSION) * sizeof(void*));
		if(!pila->datos)
			return NULL;
		pila->capacidad /= FACTOR_REDIMENSION;
		return pila->datos;
		
	}
}


/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

// Crea una pila.
// Post: devuelve una nueva pila vacía.
pila_t* pila_crear(void){
	pila_t* pila = malloc(sizeof(pila_t));

    if (!pila){
        return NULL;
    }
    pila->datos = malloc(CAP_MINIMA * sizeof(void*));

    if (!pila->datos) {
        free(pila);
        return NULL;
    }
    pila->capacidad = CAP_MINIMA;
    pila->cantidad = 0;
    return pila;
}

// Destruye la pila.
// Pre: la pila fue creada.
// Post: se eliminaron todos los elementos de la pila.
void pila_destruir(pila_t *pila){
	free(pila->datos);
	free(pila);
}

// Devuelve verdadero o falso, según si la pila tiene o no elementos apilados.
// Pre: la pila fue creada.
bool pila_esta_vacia(const pila_t *pila){
	return(pila->cantidad == 0);

}

// Agrega un nuevo elemento a la pila. Devuelve falso en caso de error.
// Pre: la pila fue creada.
// Post: se agregó un nuevo elemento a la pila, valor es el nuevo tope.
bool pila_apilar(pila_t *pila, void* valor){
	pila->cantidad += 1;
	if(pila->cantidad >= pila->capacidad){
		pila->datos = pila_redimensionar(pila, AGRANDAR);
		if(!pila->datos){
			return false;
		}
	}
	pila->datos[pila->cantidad] = valor;	
	return true;
}

// Obtiene el valor del tope de la pila. Si la pila tiene elementos,
// se devuelve el valor del tope. Si está vacía devuelve NULL.
// Pre: la pila fue creada.
// Post: se devolvió el valor del tope de la pila, cuando la pila no está
// vacía, NULL en caso contrario.
void* pila_ver_tope(const pila_t *pila){
	if(pila_esta_vacia(pila))
		return NULL;
	return(pila->datos[pila->cantidad]);
}

// Saca el elemento tope de la pila. Si la pila tiene elementos, se quita el
// tope de la pila, y se devuelve ese valor. Si la pila está vacía, devuelve
// NULL.
// Pre: la pila fue creada.
// Post: si la pila no estaba vacía, se devuelve el valor del tope anterior
// y la pila contiene un elemento menos.
void* pila_desapilar(pila_t *pila){
	if(pila_esta_vacia(pila))
		return NULL;
	void* elemento = pila->datos[pila->cantidad];
	pila->cantidad--;
	if(pila->cantidad <= pila->capacidad / CRITERIO_REDIMENSION)
		pila_redimensionar(pila, ACHICAR);
	return elemento;
}


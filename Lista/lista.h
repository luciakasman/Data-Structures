#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>



/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

/* La lista está planteada como una lista de punteros genéricos. */

struct nodo;
typedef struct nodo nodo_t;

struct lista;
typedef struct lista lista_t;

typedef struct lista_iter lista_iter_t;

/* ******************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/

// Crea una lista.
// Post: devuelve una nueva lista vacía.
lista_t *lista_crear(void);

// Devuelve verdadero o falso, según si la lista tiene o no elementos encolados.
// Pre: la lista fue creada.
bool lista_esta_vacia(const lista_t *lista);

// Devuelve verdadero o falso, según si fue posible o no insertar el elemento primero. 
// Pre: la lista fue creada.
// Post: la lista tiene como primer elemento un nodo con el dato recibido por parametro. 
bool lista_insertar_primero(lista_t *lista, void *dato);

// Devuelve verdadero o falso, según si fue posible o no insertar el elemento a lo ultimo. 
// Pre: la lista fue creada.
// Post: la lista tiene como ultimo elemento un nodo con el dato recibido por parametro. 
bool lista_insertar_ultimo(lista_t *lista, void *dato);

// Saca el primer elemento de la lista. Si la lista tiene elementos, se quita el
// primero de la lista y se devuelve su valor, si está vacía, devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el valor del primer elemento anterior, la lista
// contiene un elemento menos, si la lista no estaba vacía.
void *lista_borrar_primero(lista_t *lista);

// Obtiene el valor del primer elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del primero, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el primer elemento de la lista, cuando no está vacía.
void *lista_ver_primero(const lista_t *lista);

// Obtiene el valor del ultimo elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del ultimo, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el ultimo elemento de la lista, cuando no está vacía.
void *lista_ver_ultimo(const lista_t* lista);

// Obtiene la cantidad de elementos de la lista.
// Pre: la lista fue creada.
size_t lista_largo(const lista_t *lista);

// Destruye la lista. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la lista llama a destruir_dato.
// Pre: la lista fue creada. destruir_dato es una función capaz de destruir
// los datos de la lista, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t *lista, void destruir_dato(void *));


/* ******************************************************************
 *                	PRIMITIVAS DEL ITERADOR EXTERNO
 * *****************************************************************/

// Crea un iterador.
// Pre: la lista existe.
// Post: devuelve un iterador.
lista_iter_t *lista_iter_crear(lista_t *lista);

// Avanza el puntero actual un nodo a la derecha. Si la lista esta vacia, devuelve False.
// Pre: el iterador fue creado y la lista existe.
// Post: devuelve true si pudo avanzar, false si no. 
bool lista_iter_avanzar(lista_iter_t *iter);

// Muestra el dato del nodo al que esta apuntando actual. Si la lista esta vacia, devuelve NULL.
// Pre: el iterador fue creado y la lista existe.
// Post: devuelve el dato del nodo al que apunta.
void *lista_iter_ver_actual(const lista_iter_t *iter);

// Se fija si esta apuntando al final de la lista.
// Pre: el iterador fue creado y la lista existe.
// Post: devuelve true si el iterador apunta al final de la lista, false en caso contrario.
bool lista_iter_al_final(const lista_iter_t *iter);

// Destruye el iterador.
// Pre: el iterador fue creado y la lista existe.
void lista_iter_destruir(lista_iter_t *iter);

// Inserta un nodo con el dato pasado por parametro en la posicion en la que esta apuntando el iterador.
// Pre: el iterador fue creado y la lista existe.
// Post: devuelve true si pudo insertar el nodo, false si no.
bool lista_iter_insertar(lista_iter_t *iter, void *dato);

// Borra el nodo al que apunta el iterador. Si la lista esta vacia, devuelve NULL.
// Pre: el iterador fue creado y la lista existe.
// Post: devuelve el dato del nodo al que apuntaba el iterador, la lista
// contiene un elemento menos, si la lista no estaba vacía.
void *lista_iter_borrar(lista_iter_t *iter);


/* ******************************************************************
 * 	                 PRIMITIVA DEL ITERADOR INTERNO
 * *****************************************************************/

// Itera por todos los nodos de la lista y les aplica la funcion visitar.
// Pre: la lista fue creada.
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra);


#endif
#include "lista.h"
#include "testing.h"
#include "pila.h"
#include <stdlib.h>
#include <stdio.h>

#define TAMANIO 10
#define TAMANIO_1 100
#define TAMANIO_2 1000
#define TAMANIO_3 10000

void pruebas_lista_vacia_() {

	printf("%s\n","Pruebas con lista vacia:");

	lista_t* lista = lista_crear();
	print_test("Crear Lista Vacia", lista != NULL);

	print_test("la lista esta vacia es true", lista_esta_vacia(lista));

	print_test("ver el primero de la lista es false", !lista_ver_primero(lista));

	print_test("ver el ultimo de la lista es false", !lista_ver_ultimo(lista));

	print_test("el largo de la lista es cero", lista_largo(lista) == 0);

	print_test("borrar el primer elemento de la lista es false", !lista_borrar_primero(lista));

	lista_destruir(lista, NULL);
	print_test("la lista fue destruida", true);
}


void pruebas_lista_insertar_borrar_tamanio1() {

	printf("%s\n","Pruebas insertando 100:");

	lista_t* lista = lista_crear();

	print_test("Crear Lista Vacia", lista != NULL);

	char* vect_aux[TAMANIO_1];
	
	bool aux = true, aux2 = true, aux3 = true;

	for(int i = 0; i < TAMANIO_1/2; i++){
		
		aux &= lista_insertar_primero(lista, &vect_aux[i]);

		aux2 &= (lista_largo(lista) == i+1);

		aux3 &= (lista_ver_primero(lista) == &vect_aux[i]);
	}

	print_test("insertar primero en la lista es true", aux);

	print_test("el largo de la lista es correcto", aux2);

	print_test("el elemento insertado primero en la lista es correcto", aux3);

	for(int j = TAMANIO_1/2; j < TAMANIO_1; j++){
		
		aux &= lista_insertar_ultimo(lista, &vect_aux[j]);

		aux2 &= (lista_largo(lista) == j+1);

		aux3 &= (lista_ver_ultimo(lista) == &vect_aux[j]);
	}

	print_test("insertar ultimo en la lista es true", aux);

	print_test("el largo de la lista es correcto", aux2);

	print_test("el elemento insertado ultimo en la lista es correcto", aux3);

	for(int k = 0; k < TAMANIO_1; k++){

		aux &= (lista_ver_primero(lista) == lista_borrar_primero(lista));
		
		aux2 &= (lista_largo(lista) == TAMANIO_1-k-1);
	}

	print_test("comparar primero y valor borrado es true", aux);

	print_test("el largo de la lista es correcto", aux2);
	
	print_test("la lista esta vacia es true", lista_esta_vacia(lista));

	print_test("ver primero de la lista es false", !lista_ver_primero(lista));

	print_test("ver ultimo de la lista es false", !lista_ver_ultimo(lista));

	print_test("borrar primero de la lista es false", !lista_borrar_primero(lista));

	print_test("la lista esta vacia es true", lista_esta_vacia(lista));

	lista_destruir(lista, NULL);
	print_test("la lista fue destruida", true);

}

void pruebas_lista_insertar_borrar_tamanio2() {

	printf("%s\n","Pruebas insertando 1000:");

	lista_t* lista = lista_crear();

	print_test("Crear Lista Vacia", lista != NULL);

	char* vect_aux[TAMANIO_2];
	
	bool aux = true, aux2 = true, aux3 = true;

	for(int i = 0; i < TAMANIO_2/2; i++){
		
		aux &= lista_insertar_primero(lista, &vect_aux[i]);

		aux2 &= (lista_largo(lista) == i+1);

		aux3 &= (lista_ver_primero(lista) == &vect_aux[i]);
	}

	print_test("insertar primero en la lista es true", aux);

	print_test("el largo de la lista es correcto", aux2);

	print_test("el elemento insertado primero en la lista es correcto", aux3);

	for(int j = TAMANIO_2/2; j < TAMANIO_2; j++){
		
		aux &= lista_insertar_ultimo(lista, &vect_aux[j]);

		aux2 &= (lista_largo(lista) == j+1);

		aux3 &= (lista_ver_ultimo(lista) == &vect_aux[j]);
	}

	print_test("insertar ultimo en la lista es true", aux);

	print_test("el largo de la lista es correcto", aux2);

	print_test("el elemento insertado ultimo en la lista es correcto", aux3);

	for(int k = 0; k < TAMANIO_2; k++){

		aux &= (lista_ver_primero(lista) == lista_borrar_primero(lista));
		
		aux2 &= (lista_largo(lista) == TAMANIO_2-k-1);
	}

	print_test("comparar primero y valor borrado es true", aux);

	print_test("el largo de la lista es correcto", aux2);
	
	print_test("la lista esta vacia es true", lista_esta_vacia(lista));

	print_test("ver primero de la lista es false", !lista_ver_primero(lista));

	print_test("ver ultimo de la lista es false", !lista_ver_ultimo(lista));

	print_test("borrar primero de la lista es false", !lista_borrar_primero(lista));

	print_test("la lista esta vacia es true", lista_esta_vacia(lista));

	lista_destruir(lista, NULL);
	print_test("la lista fue destruida", true);

}

void pruebas_lista_insertar_borrar_tamanio3() {

	printf("%s\n","Pruebas insertando 10000:");

	lista_t* lista = lista_crear();

	print_test("Crear Lista Vacia", lista != NULL);

	char* vect_aux[TAMANIO_3];
	
	bool aux = true, aux2 = true, aux3 = true;

	for(int i = 0; i < TAMANIO_3/2; i++){
		
		aux &= lista_insertar_primero(lista, &vect_aux[i]);

		aux2 &= (lista_largo(lista) == i+1);

		aux3 &= (lista_ver_primero(lista) == &vect_aux[i]);
	}

	print_test("insertar primero en la lista es true", aux);

	print_test("el largo de la lista es correcto", aux2);

	print_test("el elemento insertado primero en la lista es correcto", aux3);

	for(int j = TAMANIO_3/2; j < TAMANIO_3; j++){
		
		aux &= lista_insertar_ultimo(lista, &vect_aux[j]);

		aux2 &= (lista_largo(lista) == j+1);

		aux3 &= (lista_ver_ultimo(lista) == &vect_aux[j]);
	}

	print_test("insertar ultimo en la lista es true", aux);

	print_test("el largo de la lista es correcto", aux2);

	print_test("el elemento insertado ultimo en la lista es correcto", aux3);

	for(int k = 0; k < TAMANIO_3; k++){

		aux &= (lista_ver_primero(lista) == lista_borrar_primero(lista));
		
		aux2 &= (lista_largo(lista) == TAMANIO_3-k-1);
	}

	print_test("comparar primero y valor borrado es true", aux);

	print_test("el largo de la lista es correcto", aux2);
	
	print_test("la lista esta vacia es true", lista_esta_vacia(lista));

	print_test("ver primero de la lista es false", !lista_ver_primero(lista));

	print_test("ver ultimo de la lista es false", !lista_ver_ultimo(lista));

	print_test("borrar primero de la lista es false", !lista_borrar_primero(lista));

	print_test("la lista esta vacia es true", lista_esta_vacia(lista));

	lista_destruir(lista, NULL);
	print_test("la lista fue destruida", true);

}


void comparacion_listas() {

	printf("%s\n","Pruebas de comparacion de dos listas:");

	bool aux = true, aux2 = true, aux3 = true, aux4 = true;

	lista_t* lista1 = lista_crear();

	lista_t* lista2 = lista_crear();

	print_test("Crear Lista 1 Vacia", lista1 != NULL);

	print_test("Crear Lista 2 Vacia", lista2 != NULL);

	int* elemento1 = malloc(sizeof(int));

	int* elemento2 = malloc(sizeof(int));
		
	aux = lista_insertar_primero(lista1, elemento1) && lista_insertar_ultimo(lista1, elemento2);

	aux2 = lista_insertar_primero(lista2, elemento1) && lista_insertar_ultimo(lista2, elemento2);

	print_test("el largo de la lista 1 y de la lista 2 es el mismo", lista_largo(lista1) == lista_largo(lista2));

	aux3 = (lista_ver_primero(lista1) == lista_ver_primero(lista2));

	aux4 = (lista_ver_ultimo(lista1) == lista_ver_ultimo(lista2));

	print_test("insertar elementos en la lista 1 es true", aux);

	print_test("insertar elementos en la lista 1 y la lista 2 es true", aux == aux2);

	print_test("el primero de la lista 1 y la lista 2 es el mismo", aux3);

	print_test("el ultimo de la lista 1 y la lista 2 es el mismo", aux4);

	print_test("el elemento borrado de la lista 1 es el primero que fue insertado", lista_borrar_primero(lista1) == elemento1);

	print_test("el elemento borrado de la lista 2 es el primero que fue insertado", lista_borrar_primero(lista2) == elemento1);

	print_test("el largo de la lista 1 y de la lista 2 es el mismo", lista_largo(lista1) == lista_largo(lista2));

	print_test("el primer y ultimo elemento de la lista 1 es el mismo", lista_ver_primero(lista1) == lista_ver_ultimo(lista1));

	print_test("el primer y ultimo elemento de la lista 2 es el mismo", lista_ver_primero(lista2) == lista_ver_ultimo(lista2));

	print_test("el elemento borrado de la lista 1 es el ultimo que fue insertado", lista_borrar_primero(lista1) == elemento2);

	print_test("el elemento borrado de la lista 2 es el ultimo que fue insertado", lista_borrar_primero(lista2) == elemento2);

	print_test("el largo de la lista 1 y de la lista 2 es el mismo", lista_largo(lista1) == lista_largo(lista2));

	print_test("la lista 1 esta vacia es true", lista_esta_vacia(lista1));

	print_test("la lista 1 y la 2 estan vacias es true", lista_esta_vacia(lista1) == lista_esta_vacia(lista2));

	print_test("ver primero de la lista 1 es false", !lista_ver_primero(lista1));

	print_test("ver primero de la lista 1  y de la lista 2 es false", lista_ver_primero(lista1) == lista_ver_primero(lista2));

	print_test("ver ultimo de la lista 1 es false", !lista_ver_primero(lista1));

	print_test("ver ultimo de la lista 1  y de la lista 2 es false", lista_ver_ultimo(lista1) == lista_ver_ultimo(lista2));

	print_test("borrar el primero de la lista 2 es false", !lista_borrar_primero(lista2));

	print_test("borrar el primero de las listas 1 y 2 es false", lista_borrar_primero(lista2) == lista_borrar_primero(lista1));

	free(elemento1);

	free(elemento2);
	
	lista_destruir(lista1, NULL);
	print_test("la lista 1 fue destruida", true);

	lista_destruir(lista2, NULL);
	print_test("la lista 2 fue destruida", true);
}

void pruebas_iter_insertar_borrar () {

	lista_t* lista = lista_crear();

	lista_iter_t* iter = lista_iter_crear(lista);

	print_test("Crear iterador", iter != NULL);

	char* elemento[3]; 

	print_test("Se inserto un elemento correctamente", lista_iter_insertar(iter, &elemento[0]));

	print_test("Se inserto el elemento en la primera posicion", lista_ver_primero(lista) == &elemento[0]);

	print_test("Se inserto otro elemento correctamente", lista_iter_insertar(iter, &elemento[1]));

	print_test("Se inserto otro elemento en la primera posicion", lista_ver_primero(lista) == &elemento[1]);

	print_test("Se avanzo el puntero actual correctamente", lista_iter_avanzar(iter));

	print_test("Se inserto un elemento en el medio correctamente", lista_iter_insertar(iter, &elemento[2]));

	print_test("El elemento en la ultima posicion es el correcto", lista_ver_ultimo(lista) == &elemento[0]);

	print_test("Se borro el elemento del medio correctamente", lista_iter_borrar(iter) == &elemento[2]);

	print_test("Se borro el ultimo elemento correctamente", lista_iter_borrar(iter) == &elemento[0]);

	print_test("Se intenta borrar pero como actual apunta a NULL debe dar error", !lista_iter_borrar(iter));

	print_test("El puntero esta al final de la lista", lista_iter_al_final(iter));

	lista_iter_destruir(iter);
	print_test("el iterador fue destruido", true);

	lista_destruir(lista, NULL);
}


void pruebas_iter_borrar_primero_ultimo(){

	lista_t* lista = lista_crear();

	char* elementos[3];

	bool aux = true;

	for(int i=0; i < 3; i++){

		aux &= lista_insertar_primero(lista, &elementos[i]);
	}

	print_test("Se insertan elementos en la lista correctamente", aux);

	lista_iter_t* iter = lista_iter_crear(lista); 

	print_test("Crear iterador", iter != NULL);

	print_test("El primer elemento de la lista es correcto", lista_ver_primero(lista) == &elementos[2]);

	print_test("Se borro el primer elemento correctamente", lista_iter_borrar(iter) == &elementos[2]);

	print_test("El nuevo primer elemento de la lista es correcto", lista_ver_primero(lista) == &elementos[1]);

	print_test("El ultimo elemento de la lista es correcto", lista_ver_ultimo(lista) == &elementos[0]);

	print_test("Se avanzo el puntero actual correctamente", lista_iter_avanzar(iter));

	print_test("El puntero actual se encuentra en la ultima posicion de la lista", lista_iter_ver_actual(iter) == &elementos[0]);
			
	print_test("Se borro el ultimo elemento correctamente", lista_iter_borrar(iter) == &elementos[0]);

	print_test("El nuevo ultimo elemento de la lista es correcto", lista_ver_ultimo(lista) == &elementos[1]);

	lista_iter_destruir(iter);
	print_test("el iterador fue destruido", true);

	lista_destruir(lista, NULL);
}

void pruebas_iter_borrar_medio() {

	lista_t* lista = lista_crear();

	bool aux = true, aux2 = true;

	char* elementos[10];

	for(int i=0; i < 10; i++){

		aux &= lista_insertar_primero(lista, &elementos[i]);
	}

	print_test("Se insertan elementos en la lista correctamente", aux);

	lista_iter_t* iter = lista_iter_crear(lista); 

	print_test("Crear iterador", iter != NULL);

	for(int i=0; i < 5; i++){

		aux &= lista_iter_avanzar(iter);
	}

	print_test("Se avanzo el puntero actual correctamente", aux);
	
	print_test("Se borro el elemento correctamente", lista_iter_borrar(iter) == &elementos[4]);

	lista_iter_t* iter2 = lista_iter_crear(lista); 

	print_test("Crear iterador 2", iter != NULL);

	while(!lista_iter_al_final(iter2)){

		aux &= (lista_iter_ver_actual(iter2) == &elementos[4]);

		aux2 &= lista_iter_avanzar(iter2);
	}

	print_test("Se comparan los valores que quedaron en la lista con el elemento borrado. Deberia dar False", !aux);

	print_test("Se avanzo el puntero actual correctamente", aux2);

	lista_iter_destruir(iter);
	print_test("el iterador fue destruido", true);

	lista_iter_destruir(iter2);
	print_test("el iterador fue destruido", true);

	lista_destruir(lista, NULL);
}

bool imprimir (void* dato, void* extra){

	printf("%i\n", *(int*)dato);

	return(true);
}


bool sumar_primeros_5 (void* dato, void* extra){

	if(*(int*) extra >= 35)
		return(false);

	*(int*)extra += *(int*)dato;

	return(true);
}

void pruebas_iterador_interno(){

	bool aux = true;

	int numeros[10];

	lista_t* lista = lista_crear();

	print_test("Crear Lista Vacia", lista != NULL);

	for(int i=0; i < 10; i++){

		numeros[i] = i;
		aux &= lista_insertar_primero(lista, &numeros[i]);
	}

	print_test("Se insertan elementos en la lista correctamente", aux);

	print_test("Se imprimen los elementos de la lista correctamente. Deben ser los numeros del 9 al 0.", true);	
	lista_iterar(lista, imprimir, NULL);

	int resultado = 0;

	lista_iterar(lista, sumar_primeros_5, &resultado);
	
	print_test("Se sumaron los primeros 5 elementos, debe dar 35", resultado == 35);	

	lista_destruir(lista, NULL);
	print_test("la lista fue destruida", true);
}


void destruir_dato_wrapper(void* dato){

	pila_destruir((pila_t*) dato);
}

void prueba_puntero_a_funcion() {

	printf("%s\n","Pruebas insertando pilas:");

	lista_t* lista = lista_crear();

	print_test("Crear Lista Vacia", lista != NULL);
	
	bool aux, aux2, aux3;

	pila_t* pila = pila_crear();

	pila_t* pila2 = pila_crear();

	aux = lista_insertar_primero(lista, pila);

	aux2 = (lista_ver_primero(lista) == pila);

	print_test("insertar primero la lista es true", aux);

	print_test("ver el primero de la lista es true", aux2);
	
	aux = lista_insertar_ultimo(lista, pila2);

	aux2 = (lista_ver_ultimo(lista) == pila2);

	aux3 = (lista_largo(lista) == 2);

	print_test("insertar ultimo la lista es true", aux);

	print_test("ver el ultimo de la lista es true", aux2);

	print_test("el largo de la lista es correcto", aux3);

	print_test("la lista esta vacia es false", !lista_esta_vacia(lista));

	lista_destruir(lista, destruir_dato_wrapper);
	print_test("la lista fue destruida", true);
}

void pruebas_lista_alumno() {

	pruebas_lista_vacia_();    
	pruebas_lista_insertar_borrar_tamanio1();
	pruebas_lista_insertar_borrar_tamanio2();
	pruebas_lista_insertar_borrar_tamanio3();
	comparacion_listas();
	prueba_puntero_a_funcion();

	pruebas_iter_insertar_borrar();
	pruebas_iter_borrar_primero_ultimo();
	pruebas_iter_borrar_medio();

	pruebas_iterador_interno();
}
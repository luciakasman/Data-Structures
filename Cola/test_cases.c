#include "cola.h"
#include "testing.h"
#include "pila.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#define TAMANIO 10
#define TAMANIO_1 100
#define TAMANIO_2 1000
#define TAMANIO_3 10000

void pruebas_cola_vacia_() {

	printf("%s\n","Pruebas con cola vacia:");

	cola_t* cola = cola_crear();
	print_test("Crear Cola Vacia", cola != NULL);

	print_test("la cola esta vacia es true", cola_esta_vacia(cola));

	print_test("ver el primero de la cola es false", !cola_ver_primero(cola));

	print_test("desencolar la cola es false", !cola_desencolar(cola));

	cola_destruir(cola, NULL);
	print_test("la cola fue destruida", true);
}


void pruebas_cola_encolar_desencolar_tamanio1() {

	printf("%s\n","Pruebas encolando 100:");

	cola_t* cola = cola_crear();

	print_test("Crear Cola Vacia", cola != NULL);

	char* vect_aux = malloc(sizeof(char) * TAMANIO_1);
	
	bool aux = true, aux2 = true, aux3 = true, aux4 = true;

	for(int i = 0; i < TAMANIO_1; i++){
		
		aux &= cola_encolar(cola, &vect_aux[i]);
	}

	aux2 = (cola_ver_primero(cola) == &vect_aux[0]);

	print_test("encolar la cola es true", aux);

	print_test("ver el primero de la cola es true", aux2);

	for(int j = 0; j < TAMANIO_1; j++){
		
		void* primero = cola_ver_primero(cola);

		void* desencolado = cola_desencolar(cola);
		
		aux3 &= (primero == &vect_aux[j]);

		aux4 &= (desencolado == &vect_aux[j]);
	}

	print_test("comparar primero y valor desencolado es true", aux3);

	print_test("el valor desencolado es el que fue encolado es true", aux4);
	
	print_test("la cola esta vacia es true", cola_esta_vacia(cola));

	print_test("ver primero de la cola es false", !cola_ver_primero(cola));

	print_test("desencolar la cola es false", !cola_desencolar(cola));

	free(vect_aux);

	cola_destruir(cola, NULL);
	print_test("la cola fue destruida", true);

}

void pruebas_cola_encolar_desencolar_tamanio2() {

	printf("%s\n","Pruebas encolando 1000:");

	cola_t* cola = cola_crear();

	print_test("Crear Cola Vacia", cola != NULL);

	char* vect_aux = malloc(sizeof(char) * TAMANIO_1);
	
	bool aux = true, aux2 = true, aux3 = true, aux4 = true;

	for(int i = 0; i < TAMANIO_2; i++){
		
		aux &= cola_encolar(cola, &vect_aux[i]);
	}

	aux2 = (cola_ver_primero(cola) == &vect_aux[0]);

	print_test("encolar la cola es true", aux);

	print_test("ver el primero de la cola es true", aux2);

	for(int j = 0; j < TAMANIO_2; j++){
		
		void* primero = cola_ver_primero(cola);

		void* desencolado = cola_desencolar(cola);
		
		aux3 &= (primero == &vect_aux[j]);

		aux4 &= (desencolado == &vect_aux[j]);
	}

	print_test("comparar primero y valor desencolado es true", aux3);

	print_test("el valor desencolado es el que fue encolado es true", aux4);
	
	print_test("la cola esta vacia es true", cola_esta_vacia(cola));

	print_test("ver primero de la cola es false", !cola_ver_primero(cola));

	print_test("desencolar la cola es false", !cola_desencolar(cola));

	free(vect_aux);

	cola_destruir(cola, NULL);
	print_test("la cola fue destruida", true);

}

void pruebas_cola_encolar_desencolar_tamanio3() {

	printf("%s\n","Pruebas encolando 10000:");

	cola_t* cola = cola_crear();

	print_test("Crear Cola Vacia", cola != NULL);

	char* vect_aux = malloc(sizeof(char) * TAMANIO_1);
	
	bool aux = true, aux2 = true, aux3 = true, aux4 = true;

	for(int i = 0; i < TAMANIO_3; i++){
		
		aux &= cola_encolar(cola, &vect_aux[i]);
	}

	aux2 = (cola_ver_primero(cola) == &vect_aux[0]);

	print_test("encolar la cola es true", aux);

	print_test("ver el primero de la cola es true", aux2);

	for(int j = 0; j < TAMANIO_3; j++){
		
		void* primero = cola_ver_primero(cola);

		void* desencolado = cola_desencolar(cola);
		
		aux3 &= (primero == &vect_aux[j]);

		aux4 &= (desencolado == &vect_aux[j]);
	}

	print_test("comparar primero y valor desencolado es true", aux3);

	print_test("el valor desencolado es el que fue encolado es true", aux4);
	
	print_test("la cola esta vacia es true", cola_esta_vacia(cola));

	print_test("ver primero de la cola es false", !cola_ver_primero(cola));

	print_test("desencolar la cola es false", !cola_desencolar(cola));

	free(vect_aux);

	cola_destruir(cola, NULL);
	print_test("la cola fue destruida", true);

}


void comparacion_colas() {

	printf("%s\n","Pruebas de comparacion de dos colas:");

	bool aux = true, aux2 = true, aux3 = true, aux4 = true, aux5 = true;

	cola_t* cola1 = cola_crear();

	cola_t* cola2 = cola_crear();

	print_test("Crear Cola 1 Vacia", cola1 != NULL);

	print_test("Crear Cola 2 Vacia", cola2 != NULL);

	print_test("encolar elemento NULL en Cola 1 es true", cola_encolar(cola1, NULL));

	print_test("encolar elemento NULL en Cola 2 es true", cola_encolar(cola2, NULL));

	for(int i = 0; i < TAMANIO; i++){
		
		aux &= cola_encolar(cola1, &i);

		aux2 &= cola_encolar(cola2, &i);
	}

	aux3 = (cola_ver_primero(cola1) == cola_ver_primero(cola2));

	print_test("encolar la cola 1 es true", aux);

	print_test("encolar la cola 1 y la cola 2 es true", aux == aux2);

	print_test("el primero de la cola 1 y de la 2 es el mismo", aux3);

	for(int j = 0; j <= TAMANIO; j++){

		void* primero1 = cola_ver_primero(cola1);

		void* primero2 = cola_ver_primero(cola2);
		
		void* desencolado1 = cola_desencolar(cola1);

		void* desencolado2 = cola_desencolar(cola2);

		aux4 &= (primero1 == desencolado2);

		aux5 &= (primero2 == desencolado1);
	}

	print_test("comparar primero de la cola 1 y valor desencolado de la cola 2 es true", aux4);

	print_test("comparar primero de la cola 2 y valor desencolado de la cola 1 es true", aux5);
	
	print_test("la cola 1 esta vacia es true", cola_esta_vacia(cola1));

	print_test("la cola 1 y la 2 estan vacias es true", cola_esta_vacia(cola1) == cola_esta_vacia(cola2));

	print_test("ver primero de la cola 1 es false", !cola_ver_primero(cola1));

	print_test("ver primero de la cola 1  y de la cola 2 es false", cola_ver_primero(cola1) == cola_ver_primero(cola2));

	print_test("desencolar la cola 2 es false", !cola_desencolar(cola2));

	print_test("desencolar las colas 1 y 2 es false", cola_desencolar(cola2) == cola_desencolar(cola1));


	cola_destruir(cola1, NULL);
	print_test("la cola 1 fue destruida", true);

	cola_destruir(cola2, NULL);
	print_test("la cola 2 fue destruida", true);

}


void destruir_dato_wrapper(void* dato){

	pila_destruir((pila_t*) dato);

}

void prueba_puntero_a_funcion() {

	printf("%s\n","Pruebas encolando pilas:");

	cola_t* cola = cola_crear();

	print_test("Crear Cola Vacia", cola != NULL);
	
	bool aux = true, aux2 = true;

	pila_t* pila = pila_crear();

	aux = cola_encolar(cola, pila);

	aux2 = (cola_ver_primero(cola) == pila);

	print_test("encolar la cola es true", aux);

	print_test("ver el primero de la cola es true", aux2);
	
	print_test("la cola esta vacia es false", !cola_esta_vacia(cola));

	cola_destruir(cola, destruir_dato_wrapper);
	print_test("la cola fue destruida", true);
}

void pruebas_cola_alumno() {

	pruebas_cola_vacia_();    
	pruebas_cola_encolar_desencolar_tamanio1();
	pruebas_cola_encolar_desencolar_tamanio2();
	pruebas_cola_encolar_desencolar_tamanio3();
	comparacion_colas();
	prueba_puntero_a_funcion();
}

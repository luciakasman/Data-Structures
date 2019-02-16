#include "pila.h"
#include "testing.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#define TAMANIO 1
#define TAMANIO_1 100
#define TAMANIO_2 1000
#define TAMANIO_3 10000
/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/
void pruebas_pila_vacia_() {

	printf("%s\n","Pruebas con pila vacia:");

	pila_t* pila = pila_crear();
	print_test("Crear Pila Vacia", pila != NULL);

	print_test("la pila esta vacia es true", pila_esta_vacia(pila));

	print_test("ver tope de la pila es false", !pila_ver_tope(pila));

	print_test("desapilar la pila es false", !pila_desapilar(pila));

	pila_destruir(pila);
	print_test("la pila fue destruida", true);
}

void pruebas_pila_apilar_desapilar_tamanio1() {

	printf("%s\n","Pruebas apilando 100:");

	pila_t* pila = pila_crear();

	print_test("Crear Pila Vacia", pila != NULL);

	char* vect_aux = malloc(sizeof(char) * TAMANIO_1);
	
	bool aux = true, aux2 = true, aux3 = true, aux4 = true;

	for(int i = 0; i < TAMANIO_1; i++){
		
		aux &= pila_apilar(pila, &vect_aux[i]);
		
		aux2 &= (pila_ver_tope(pila) == &vect_aux[i]);
	}

	print_test("apilar la pila es true", aux);

	print_test("ver tope de la pila al apilar es true", aux2);

	for(int j = TAMANIO_1 -1 ; j >= 0; j--){
		
		void* tope = pila_ver_tope(pila);

		void* desapilado = pila_desapilar(pila);
		
		aux3 &= (tope == &vect_aux[j]);

		aux4 &= (desapilado == &vect_aux[j]);
	}

	print_test("comparar tope y valor desapilado es true", aux3);

	print_test("el valor desapilado es el que fue apilado es true", aux4);
	
	print_test("la pila esta vacia es true", pila_esta_vacia(pila));

	print_test("ver tope de la pila es false", !pila_ver_tope(pila));

	print_test("desapilar la pila es false", !pila_desapilar(pila));

	free(vect_aux);

	pila_destruir(pila);
	print_test("la pila fue destruida", true);

}

void pruebas_pila_apilar_desapilar_tamanio2() {

	printf("%s\n","Pruebas apilando 1000:");

	pila_t* pila = pila_crear();
	print_test("Crear Pila Vacia", pila != NULL);
	
	bool aux = true, aux2 = true, aux3 = true, aux4 = true;

	char* vect_aux = malloc(sizeof(char) * TAMANIO_2);

	for(int i = 0; i < TAMANIO_2; i++){
		
		aux &= pila_apilar(pila, &vect_aux[i]);
		
		aux2 &= (pila_ver_tope(pila) == &vect_aux[i]);
	}

	print_test("apilar la pila es true", aux);

	print_test("ver tope de la pila al apilar es true", aux2);

	for(int j = TAMANIO_2 - 1; j >= 0; j--){
		
		void* tope = pila_ver_tope(pila);

		void* desapilado = pila_desapilar(pila);
		
		aux3 &= (tope == desapilado);

		aux4 &= (desapilado == &vect_aux[j]);
	}

	print_test("comparar tope y valor desapilado es true", aux3);

	print_test("el valor desapilado es el que fue apilado es true", aux4);
	
	print_test("la pila esta vacia es true", pila_esta_vacia(pila));

	print_test("ver tope de la pila es false", !pila_ver_tope(pila));

	print_test("desapilar la pila es false", !pila_desapilar(pila));
	
	free(vect_aux);

	pila_destruir(pila);
	print_test("la pila fue destruida", true);

}

void pruebas_pila_apilar_desapilar_tamanio3() {

	printf("%s\n","Pruebas apilando 10000:");
	
	pila_t* pila = pila_crear();
	print_test("Crear Pila Vacia", pila != NULL);
	
	bool aux = true, aux2 = true, aux3 = true, aux4 = true;

	char* vect_aux = malloc(sizeof(char) * TAMANIO_3);

	for(int i = 0; i < TAMANIO_3; i++){
		
		aux &= pila_apilar(pila, &vect_aux[i]);
		
		aux2 &= (pila_ver_tope(pila) == &vect_aux[i]);
	}

	print_test("apilar la pila es true", aux);

	print_test("ver tope de la pila al apilar es true", aux2);

	for(int j = TAMANIO_3 - 1 ; j >= 0; j--){
		
		void* tope = pila_ver_tope(pila);

		void* desapilado = pila_desapilar(pila);
		
		aux3 &= (tope == desapilado);

		aux4 &= (desapilado == &vect_aux[j]);
	}

	print_test("comparar tope y valor desapilado es true", aux3);

	print_test("el valor desapilado es el que fue apilado es true", aux4);
	
	print_test("la pila esta vacia es true", pila_esta_vacia(pila));

	print_test("ver tope de la pila es false", !pila_ver_tope(pila));

	print_test("desapilar la pila es false", !pila_desapilar(pila));

	free(vect_aux);

	pila_destruir(pila);
	print_test("la pila fue destruida", true);

}

void comparacion_pilas() {

	printf("%s\n","Pruebas de comparacion de dos pilas:");

	bool aux = true, aux2 = true, aux3 = true, aux4 = true, aux5 = true;

	pila_t* pila1 = pila_crear();

	pila_t* pila2 = pila_crear();

	//print_test("Crear Pila 1 Vacia", pila1 != NULL);

	print_test("Crear Pila 2 Vacia", pila2 != NULL);

	print_test("apilar elemento NULL en Pila 1 es true", pila_apilar(pila1, NULL));

	print_test("apilar elemento NULL en Pila 2 es true", pila_apilar(pila2, NULL));

	for(int i = 0; i < TAMANIO; i++){
		
		aux &= pila_apilar(pila1, &i);

		aux2 &= pila_apilar(pila2, &i);
		
		aux3 &= (pila_ver_tope(pila1) == pila_ver_tope(pila2));

	}

	print_test("apilar la pila 1 es true", aux);

	print_test("apilar la pila 1 y la pila 2 es true", aux == aux2);

	print_test("el tope de la pila 1 y la 2 es el mismo", aux3);

	for(int j = TAMANIO; j >= 0; j--){

		void* tope1 = pila_ver_tope(pila1);

		void* tope2 = pila_ver_tope(pila2);
		
		void* desapilado1 = pila_desapilar(pila1);

		void* desapilado2 = pila_desapilar(pila2);

		aux4 &= (tope1 == desapilado2);

		aux5 &= (tope2 == desapilado1);
	}

	print_test("comparar tope de la pila 1 y valor desapilado de la pila 2 es true", aux4);

	print_test("comparar tope de la pila 2 y valor desapilado de la pila 1 es true", aux5);
	
	print_test("la pila 1 esta vacia es true", pila_esta_vacia(pila1));

	print_test("la pila 1 y la 2 estan vacias es true", pila_esta_vacia(pila1) == pila_esta_vacia(pila2));

	print_test("ver tope de la pila 1 es false", !pila_ver_tope(pila1));

	print_test("ver tope de la pila 1  y de la pila 2 es false", pila_ver_tope(pila1) == pila_ver_tope(pila2));

	print_test("desapilar la pila 2 es false", !pila_desapilar(pila2));

	print_test("desapilar las pilas 1 y 2 es false", pila_desapilar(pila2) == pila_desapilar(pila1));


	pila_destruir(pila1);
	print_test("la pila 1 fue destruida", true);

	pila_destruir(pila2);
	print_test("la pila 2 fue destruida", true);

}


void pruebas_pila_alumno() {
    pila_t* ejemplo = NULL;
    
    print_test("Puntero inicializado a NULL", ejemplo == NULL);

    pruebas_pila_vacia_(); 
    pruebas_pila_apilar_desapilar_tamanio1();
    pruebas_pila_apilar_desapilar_tamanio2();
    pruebas_pila_apilar_desapilar_tamanio3();
    comparacion_pilas();
}

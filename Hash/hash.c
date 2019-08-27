#define _POSIX_C_SOURCE 200809L
#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#define NO_ENCONTRADO -1
#define CAPACIDAD_INICIAL 53
#define CARGA_MAXIMA 0.3
#define CARGA_MINIMA 0.25
#define FACTOR_AGRANDAR 2
#define FACTOR_ACHICAR 0.75

typedef enum{VACIO, OCUPADO, BORRADO} estado_t;

typedef struct campo{
	char* clave;
	void* dato;
	estado_t estado;
}campo_t;

struct hash{
	campo_t** tabla;
	size_t capacidad;
	size_t cantidad;
	hash_destruir_dato_t destruir_dato;
};

struct hash_iter{
	const hash_t* hash_actual;
	size_t pos_actual;
};

/* ******************************************************************
 *                        AUXILIARES
 * *****************************************************************/

unsigned int HashFunc(const char* str, size_t length) {
	unsigned int hash = 0;
	unsigned int i = 0;

	for (i = 0; i < length; str++, i++)
	{
		hash = (*str) + (hash << 6) + (hash << 16) - hash;
	}

	return hash;
}

campo_t** tabla_crear(hash_t* hash, size_t tam){

	campo_t** tabla = calloc(tam, sizeof(campo_t*));

	if(!tabla){
		return NULL;
	}

	for(int i = 0; i < tam; i++){
		campo_t* campo = malloc(sizeof(campo_t));
		campo->clave = "\0";
		campo->estado = VACIO;
		campo->dato = NULL;
		tabla[i] = campo;
	}

	return tabla;
}


long unsigned int clave_buscar(const hash_t* hash, const char* clave, size_t* pos_vacio){

	long unsigned int pos = (HashFunc(clave, strlen(clave)) % hash->capacidad);

	size_t cont = 0;

	while(hash->tabla[pos]->estado != VACIO){

		if(strcmp(hash->tabla[pos]->clave, clave) == 0)
			return pos;

		pos++;
		cont++;

		if(pos == hash->capacidad)
			pos = 0;

		if(cont == hash->capacidad){
			*pos_vacio = pos;
			return NO_ENCONTRADO;
		}
	}
	*pos_vacio = pos;
	return NO_ENCONTRADO;
}

void hash_redimensionar(hash_t* hash, double accion){

	if(accion == FACTOR_ACHICAR && hash->capacidad <= CAPACIDAD_INICIAL){
		return;
	}

	double tam_nuevo = (double)hash->capacidad * accion;

	size_t tam_viejo = hash->capacidad;

	campo_t** vieja = hash->tabla;

	campo_t** nueva = tabla_crear(hash, (size_t)tam_nuevo);

	if(nueva == NULL){
		return;
	}

	hash->tabla = nueva;
	hash->capacidad = (size_t)tam_nuevo;
	hash->cantidad = 0;

	for(int i = 0; i < tam_viejo; i++){
		if(vieja[i]->estado == OCUPADO){
			hash_guardar(hash, vieja[i]->clave, vieja[i]->dato);
			free(vieja[i]->clave);
		}
		free(vieja[i]);
	}
	free(vieja);
		
}

/* ******************************************************************
 *                       PRIMITIVAS
 * *****************************************************************/

hash_t *hash_crear(hash_destruir_dato_t destruir_dato){

	hash_t* hash = malloc(sizeof(hash_t));

	if(!hash) return NULL;

	campo_t** tabla = tabla_crear(hash, CAPACIDAD_INICIAL);

	if(!tabla) return NULL;

	hash->tabla = tabla;
	hash->capacidad = CAPACIDAD_INICIAL;
	hash->cantidad = 0;
	hash->destruir_dato = destruir_dato;

	return hash;

}

bool hash_pertenece(const hash_t *hash, const char *clave){

	size_t buff = 0;

	long unsigned int pos_clave = clave_buscar(hash, clave, &buff);

	if(pos_clave == NO_ENCONTRADO)
		return false;

	return true; 
	
}

bool hash_guardar(hash_t *hash, const char *clave, void *dato){

	size_t pos_vacio = 0;

	long unsigned int pos_clave = clave_buscar(hash, clave, &pos_vacio);

	if(pos_clave != NO_ENCONTRADO){
		
		if(hash->destruir_dato)
			hash->destruir_dato(hash->tabla[pos_clave]->dato);
			
		hash->tabla[pos_clave]->dato = dato;
		return true;
	}

	char* clave_aux = malloc(sizeof(char) * (strlen(clave) + 1));	
	
	if(!clave_aux)
		return false;
	
	strcpy(clave_aux, clave);
	
	hash->tabla[pos_vacio]->clave = clave_aux;
	hash->tabla[pos_vacio]->dato = dato;
	hash->tabla[pos_vacio]->estado = OCUPADO;

	hash->cantidad++;

	if((double)hash->cantidad >= (CARGA_MAXIMA * (double)hash->capacidad)){
		hash_redimensionar(hash, FACTOR_AGRANDAR);
	}

	return true;

}

void *hash_borrar(hash_t *hash, const char *clave){

	size_t buff = 0;

	long unsigned int pos_borrar = clave_buscar(hash, clave, &buff);

	if(pos_borrar == NO_ENCONTRADO)
		return NULL;

	void* dato = hash->tabla[pos_borrar]->dato;
	hash->tabla[pos_borrar]->estado = BORRADO;
	free(hash->tabla[pos_borrar]->clave);
	hash->tabla[pos_borrar]->clave = "\0";
	hash->tabla[pos_borrar]->dato = NULL;

	hash->cantidad--;

	if(hash->capacidad > CAPACIDAD_INICIAL && hash->cantidad <= (CARGA_MINIMA * (double)hash->capacidad)){
		hash_redimensionar(hash, FACTOR_ACHICAR);
	}

	return dato;

}


size_t hash_cantidad(const hash_t *hash){
	return hash->cantidad;

}

void* hash_obtener(const hash_t *hash, const char *clave){

	size_t buff = 0;

	long unsigned int esta = clave_buscar(hash, clave, &buff);

	if(esta == NO_ENCONTRADO){
		return NULL;
	}

	return hash->tabla[esta]->dato;	

}

void hash_destruir(hash_t *hash){
	
	for(int i = 0; i < hash->capacidad; i++){
		if(hash->tabla[i]->estado == OCUPADO){
			free(hash->tabla[i]->clave);
			if(hash->destruir_dato)
				hash->destruir_dato(hash->tabla[i]->dato);
		}
		free(hash->tabla[i]);
	}
	free(hash->tabla);
	free(hash);
}


/* *******************************************************
 *                      ITERADOR
 * *******************************************************/

/* Iterador del hash */

hash_iter_t *hash_iter_crear(const hash_t *hash){
	
	hash_iter_t* iter = malloc(sizeof(hash_iter_t));

	if(!iter) 
		return NULL;
	iter->hash_actual = hash;
	iter->pos_actual= 0;

	while(iter->pos_actual < iter->hash_actual->capacidad && hash->tabla[iter->pos_actual]->estado != OCUPADO)
		iter->pos_actual++;

	return iter;
}

bool hash_iter_avanzar(hash_iter_t *iter){

	if(hash_iter_al_final(iter)) 
		return false;

	size_t aux = iter->pos_actual + 1;

	while(aux < iter->hash_actual->capacidad && iter->hash_actual->tabla[aux]->estado != OCUPADO)
		aux++;

	iter->pos_actual = aux;

	return true;
}


const char *hash_iter_ver_actual(const hash_iter_t *iter){
	if(hash_iter_al_final(iter)) 
		return NULL;
	return iter->hash_actual->tabla[iter->pos_actual]->clave;
}


bool hash_iter_al_final(const hash_iter_t *iter){
	return(iter->pos_actual == iter->hash_actual->capacidad);
}


void hash_iter_destruir(hash_iter_t* iter){
	free(iter);
}
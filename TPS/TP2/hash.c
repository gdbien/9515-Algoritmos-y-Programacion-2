#define _GNU_SOURCE 1
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include <limits.h>

#define TAM_HASH 5011
#define MAX_FACTOR 0.7
#define MIN_FACTOR 0.2
#define FACTOR_AGRANDAR 2
#define FACTOR_REDUCCION 0.5
#define BORRADO 'B'
#define OCUPADO 'O'
#define VACIO '\0'

typedef struct hash_campo {
	char* clave;
	void* valor;
  char estado;
} hash_campo_t;

struct hash {
	hash_campo_t* tabla;
	size_t tam;
	size_t cant;
	hash_destruir_dato_t destruir_dato;
};

struct hash_iter {
	hash_t* hash;
	size_t actual;
};

/******************** FUNCIÓN DE HASH ********************/

static size_t hash_function(const char* cp, size_t tam) {
    size_t hash = 0;
    while (*cp)
        hash = (hash * 10) + *cp++ - '0';
    return hash%tam;
}

/******************** FUNCIONES AUXILIARES ********************/

void destruir_tabla(hash_campo_t* tabla, size_t tam, hash_destruir_dato_t destruir_dato) {
	for(size_t i = 0; i < tam; i++) {
		if(tabla[i].estado) {
      if(tabla[i].estado == OCUPADO) {
        if(destruir_dato) destruir_dato(tabla[i].valor);
      }
      free(tabla[i].clave);
    }
	}
	free(tabla);
}

hash_campo_t* crear_tabla(size_t tam) {
	hash_campo_t* tabla = calloc(tam, sizeof(hash_campo_t));
	if(!tabla) return NULL;
	return tabla;
}

size_t posicion_valida_siguiente(const hash_t* hash, size_t posicion_actual) {
	bool pos_valida = false;
	while(posicion_actual < hash->tam && !pos_valida) {
    if(!hash->tabla[posicion_actual].estado) posicion_actual++;
		else if(hash->tabla[posicion_actual].estado == BORRADO) posicion_actual++;
    else pos_valida = true;
	}
	//if(!pos_valida) posicion_actual = hash->tam; //al final
	return posicion_actual;
}

bool redimensionar_hash(hash_t* hash, size_t tam_nuevo) {
	hash_campo_t* tabla_aux = hash->tabla;
	hash->tabla = crear_tabla(tam_nuevo);
	if(!hash->tabla) return false;
	hash->cant = 0;
	size_t tam_viejo = hash->tam;
	hash->tam = tam_nuevo;
	for(size_t i = 0; i < tam_viejo; i++) {
    hash_campo_t hash_campo = tabla_aux[i];
    if(hash_campo.estado == OCUPADO) {
      size_t pos_tabla = hash_function(hash_campo.clave, hash->tam);
      while(hash->tabla[pos_tabla].estado != VACIO) pos_tabla++;
      hash->tabla[pos_tabla] = hash_campo;
      hash->cant++;
    }
	}
  free(tabla_aux);
	return true;
}

/******************** PRIMITIVAS HASH ********************/

hash_t *hash_crear(hash_destruir_dato_t destruir_dato) {
	hash_t* hash = malloc(sizeof(hash_t));
	if(!hash) return NULL;
	hash->tabla = crear_tabla(TAM_HASH);
	if(!hash->tabla) {
		free(hash);
		return NULL;
	}
	hash->tam = TAM_HASH;
	hash->cant = 0;
	hash->destruir_dato = destruir_dato;
	return hash;
}

bool hash_guardar(hash_t *hash, const char *clave, void *dato) {
	size_t pos_tabla = hash_function(clave, hash->tam);

  while(pos_tabla < hash->tam && hash->tabla[pos_tabla].estado != VACIO) {
    if(hash->tabla[pos_tabla].estado == BORRADO) (pos_tabla)++;
    else if(strcmp(hash->tabla[pos_tabla].clave, clave) == 0) {
      if(hash->destruir_dato) hash->destruir_dato(hash->tabla[pos_tabla].valor);
      hash->tabla[pos_tabla].valor = dato;
      return true;
    }
    else (pos_tabla)++;
  }

  hash->tabla[pos_tabla].clave = strdup(clave);
  if(!hash->tabla[pos_tabla].clave) return NULL;
  hash->tabla[pos_tabla].estado = OCUPADO;
  hash->tabla[pos_tabla].valor = dato;
	hash->cant++;

	double factor_hash = (double)hash->cant/(double)hash->tam;
 	if(factor_hash >= MAX_FACTOR) redimensionar_hash(hash, (size_t)((double) hash->tam*FACTOR_AGRANDAR));
	return true;
}

void *hash_borrar(hash_t *hash, const char *clave) {

	size_t pos_tabla = hash_function(clave, hash->tam);

  while(pos_tabla < hash->tam && hash->tabla[pos_tabla].estado != VACIO) {
    if(hash->tabla[pos_tabla].estado == BORRADO) (pos_tabla)++;
    else if(strcmp(hash->tabla[pos_tabla].clave, clave) == 0) {
      hash->tabla[pos_tabla].estado = BORRADO;
      void* dato = hash->tabla[pos_tabla].valor;
      hash->cant--;

      double factor_hash = (double) hash->cant / (double) hash->tam;
      if(factor_hash <= MIN_FACTOR && hash->tam > TAM_HASH) redimensionar_hash(hash, (size_t)((double)hash->tam*FACTOR_REDUCCION));

      return dato;
    }
    else (pos_tabla)++;
  }

	return NULL;
}

void *hash_obtener(const hash_t *hash, const char *clave) {
	size_t pos_tabla = hash_function(clave, hash->tam);
  hash_campo_t* tabla = hash->tabla;
  while(pos_tabla < hash->tam && tabla[pos_tabla].estado != VACIO) {
    if(tabla[pos_tabla].estado == BORRADO) (pos_tabla)++;
    else if(strcmp(tabla[pos_tabla].clave, clave) == 0) return tabla[pos_tabla].valor;
    else (pos_tabla)++;
  }
  return NULL;
}

bool hash_pertenece(const hash_t *hash, const char *clave) {
	size_t pos_tabla = hash_function(clave, hash->tam);
  hash_campo_t* tabla = hash->tabla;
  while(pos_tabla < hash->tam && tabla[pos_tabla].estado != VACIO) {
    if(tabla[pos_tabla].estado == BORRADO) (pos_tabla)++;
    else if(strcmp(tabla[pos_tabla].clave, clave) == 0) return true;
    else (pos_tabla)++;
  }
  return false;
}

size_t hash_cantidad(const hash_t *hash) {
	return hash->cant;
}

void hash_destruir(hash_t *hash) {
	destruir_tabla(hash->tabla, hash->tam, hash->destruir_dato);
  free(hash);
}

/******************** PRIMITIVAS ITER HASH ********************/

hash_iter_t *hash_iter_crear(const hash_t *hash) {
	hash_iter_t* hash_iter = malloc(sizeof(hash_iter_t));
	if(!hash_iter) return NULL;
  hash_iter->hash = (hash_t*) hash;
	hash_iter->actual = posicion_valida_siguiente(hash, 0);
  return hash_iter;
}

bool hash_iter_avanzar(hash_iter_t *iter) {
	if(hash_iter_al_final(iter)) return false;
	iter->actual = posicion_valida_siguiente(iter->hash, iter->actual+1);
  return true;
}

const char *hash_iter_ver_actual(const hash_iter_t *iter) {
	if(hash_iter_al_final(iter)) return NULL;
	hash_campo_t hash_campo = iter->hash->tabla[iter->actual];
	return hash_campo.clave;
}

bool hash_iter_al_final(const hash_iter_t *iter) {
	return (iter->actual == iter->hash->tam);
}

void hash_iter_destruir(hash_iter_t* iter) {
  free(iter);
}

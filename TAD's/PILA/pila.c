#include "pila.h"
#include <stdlib.h>

#define CAPACIDAD 10
#define FACTOR_REDIMENSION_2 2
#define FACTOR_REDIMENSION_4 4

/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void** datos;
    size_t cantidad;  // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/
bool redimensionar(pila_t* pila,size_t tamanio) {
	void** datos_nuevo=realloc(pila->datos,tamanio*sizeof(void*));
	if (!datos_nuevo) {
		return false;
	}
	pila->capacidad=tamanio;
	pila->datos=datos_nuevo;
	return true;
}

pila_t* pila_crear(void) {
	pila_t* pila=malloc(sizeof(pila_t));
	if (!pila) {
		return NULL;
	}
	pila->datos=malloc(CAPACIDAD*sizeof(void*));
	if (!pila->datos) {
		free(pila);
		return NULL;
	}
	pila->cantidad=0;
	pila->capacidad=CAPACIDAD;
	return pila;
}

void pila_destruir(pila_t *pila) {
	free(pila->datos);
	free(pila);
}

bool pila_esta_vacia(const pila_t *pila) {
	return pila->cantidad==0;
}

bool pila_apilar(pila_t *pila, void* valor) {
	if (pila->cantidad+1 > pila->capacidad) {
		if (!redimensionar(pila,pila->capacidad*FACTOR_REDIMENSION_2)) {
			return false;
		}
	}
	pila->datos[pila->cantidad]=valor;
	pila->cantidad++;
	return true;
}

void* pila_ver_tope(const pila_t *pila) {
	if (pila_esta_vacia(pila)) {
		return NULL;
	}
	return pila->datos[pila->cantidad-1];
}

void* pila_desapilar(pila_t *pila) {
	if (pila_esta_vacia(pila)) {
		return NULL;
	}
	void* tope=pila_ver_tope(pila);
	if (pila->cantidad <= pila->capacidad/FACTOR_REDIMENSION_4) {
		if (pila->capacidad/FACTOR_REDIMENSION_4 > CAPACIDAD) {
			redimensionar(pila,pila->capacidad/FACTOR_REDIMENSION_2);
		}
	}
	pila->cantidad--;
	return tope;
}
// ...

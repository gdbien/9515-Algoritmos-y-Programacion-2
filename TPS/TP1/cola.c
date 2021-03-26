#include "cola.h"

typedef struct nodo {
	void* dato;
	struct nodo* proximo;
} nodo_t;

struct cola {
	nodo_t* primero;
	nodo_t* ultimo;
	size_t cantidad;
};

size_t cola_ver_tamanio(cola_t* cola) {
	return cola->cantidad;
}

cola_t* cola_crear(void) {
	cola_t* cola=malloc(sizeof(cola_t));
	if (!cola) {
		return NULL;
	}
	cola->primero=NULL;
	cola->ultimo=NULL;
	cola->cantidad=0;
	return cola;
}

bool cola_encolar(cola_t *cola, void* valor) {
	nodo_t* nodo=malloc(sizeof(nodo_t));
	if (!nodo) {
		return false;
	}
	nodo->dato=valor;
	nodo->proximo=NULL;
	if (cola_esta_vacia(cola)) {
		cola->primero=nodo;
	} else {
		cola->ultimo->proximo=nodo;
	}
	cola->ultimo=nodo;
	cola->cantidad++;
	return true;
}

bool cola_esta_vacia(const cola_t *cola) {
	return cola->primero==NULL;
}

void* cola_ver_primero(const cola_t *cola) {
	if (cola_esta_vacia(cola)) {
		return NULL;
	}
	return cola->primero->dato;
}

void* cola_desencolar(cola_t *cola) {
	if (cola_esta_vacia(cola)) {
		return NULL;
    }
	void* datoPrimero=cola_ver_primero(cola);
    nodo_t* auxiliar=cola->primero;
	if (cola->primero==cola->ultimo) {
		cola->ultimo=NULL;
	} 
	cola->primero=cola->primero->proximo;
	free(auxiliar);
	cola->cantidad--;
	return datoPrimero;
}

void cola_destruir(cola_t *cola, void destruir_dato(void*)) {
	while (cola->primero) {
		nodo_t* actual=cola->primero;
		cola->primero=cola->primero->proximo;
		if (destruir_dato) {
			destruir_dato(actual->dato);
		}
		free(actual);
	}
	free(cola);		
}

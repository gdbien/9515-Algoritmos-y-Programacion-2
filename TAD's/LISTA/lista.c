#include "lista.h"
#include <stdlib.h>


typedef struct nodo {
	void* dato;
	struct nodo* proximo;
} nodo_t;

struct lista {
	nodo_t* primero;
	nodo_t* ultimo;
	size_t largo;
};

struct lista_iter {
	nodo_t* actual;
	nodo_t* anterior;
	lista_t* lista;
};

lista_t *lista_crear(void) {
	lista_t* lista=malloc(sizeof(lista_t));
	if (!lista) {
		return NULL;
	}
	lista->primero=NULL;
	lista->ultimo=NULL;
	lista->largo=0;
	return lista;
}

nodo_t* nodo_crear(void* dato) {
	nodo_t* nodo=malloc(sizeof(nodo_t));
	if (!nodo) {
		return NULL;
	}
	nodo->dato=dato;
	nodo->proximo=NULL;
	return nodo;
}

void* nodo_destruir(nodo_t* nodo) {
 	void* dato=nodo->dato;
 	free(nodo);
	return dato;
}

bool lista_esta_vacia(const lista_t *lista) {
	return lista_largo(lista)==0;
}

bool lista_insertar_primero(lista_t *lista, void *dato) {
	nodo_t* nodo=nodo_crear(dato);
	if (!nodo) {
		return false;
	}
	if (lista_esta_vacia(lista)) {
		lista->ultimo=nodo;
	} else {
		nodo->proximo=lista->primero;
	}
	lista->primero=nodo;
	lista->largo++;
	return true;
}

bool lista_insertar_ultimo(lista_t *lista, void *dato) {
	if (lista_esta_vacia(lista)) {
		return lista_insertar_primero(lista,dato);
	}
	nodo_t* nodo=nodo_crear(dato);
	if (!nodo) {
		return false;
	}
	lista->ultimo->proximo=nodo;
	lista->ultimo=nodo;
	lista->largo++;
	return true;
}

size_t lista_largo(const lista_t *lista) {
	return lista->largo;
}

void *lista_borrar_primero(lista_t *lista) {
	if (lista_esta_vacia(lista)) {
		return NULL;
	}
	nodo_t* nodo=lista->primero;
	if (lista_largo(lista)==1) {
		lista->ultimo=NULL;
	}
	lista->primero=lista->primero->proximo;
	(lista->largo)--;
	return nodo_destruir(nodo);
}

void *lista_ver_primero(const lista_t *lista) {
	if (lista_esta_vacia(lista)) {
		return NULL;
	}
	return lista->primero->dato;
}

void *lista_ver_ultimo(const lista_t* lista) {
	if (lista_esta_vacia(lista)) {
		return NULL;
	}
	return lista->ultimo->dato;
}

void lista_destruir(lista_t *lista, void destruir_dato(void *)) {
	while (lista->primero) {
		nodo_t* actual=lista->primero;
		if (destruir_dato) {
			destruir_dato(actual->dato);
		}
		lista->primero=lista->primero->proximo;
		free(actual);
	}
	free(lista);
}

void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra) {
	if (!visitar) {
		return;
	}
	nodo_t* actual=lista->primero;
	while (actual) {
		if (visitar(actual->dato,extra)==false) {
			return;
		}
		actual=actual->proximo;
	}
}

lista_iter_t *lista_iter_crear(lista_t *lista){
	lista_iter_t* iter=malloc(sizeof(lista_iter_t)); 
	if (!iter) {									
		return NULL;
	}
	iter->lista=lista;
	if (iter->lista->primero) {
		iter->actual=iter->lista->primero;
		iter->anterior=NULL;
	} else {
		iter->actual=iter->lista->ultimo;
		iter->anterior=NULL;
	}
	return iter;
}

bool lista_iter_avanzar(lista_iter_t *iter) {
	if (lista_iter_al_final(iter)) {
		return false;
	}
	iter->anterior=iter->actual;
	iter->actual=iter->actual->proximo;
	return true;
}

void *lista_iter_ver_actual(const lista_iter_t *iter) {
	if (lista_iter_al_final(iter)) {
		return NULL;
	}
	return iter->actual->dato;
}

bool lista_iter_al_final(const lista_iter_t *iter) {
	return !iter->actual;
}

void lista_iter_destruir(lista_iter_t *iter) {
	free(iter);
}

bool lista_iter_insertar(lista_iter_t *iter, void *dato) {
	nodo_t* nodo=nodo_crear(dato);
	if (!nodo) return false;
	if (!iter->anterior) iter->lista->primero=nodo;
	else iter->anterior->proximo=nodo;
	if (lista_iter_al_final(iter)) iter->lista->ultimo=nodo;
	else nodo->proximo=iter->actual;
	iter->actual=nodo;
	iter->lista->largo++;
	return true;
}

void *lista_iter_borrar(lista_iter_t *iter) {
	if (lista_iter_al_final(iter)) {
		return NULL;
	}
	nodo_t* actual=iter->actual;
	if (!iter->anterior) iter->lista->primero=iter->actual->proximo;
	else iter->anterior->proximo=iter->actual->proximo;
	if (!iter->actual->proximo) iter->lista->ultimo=iter->anterior;
	iter->actual=iter->actual->proximo;
	iter->lista->largo--;
	return nodo_destruir(actual);
}

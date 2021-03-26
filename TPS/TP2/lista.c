#include"lista.h"
#include<stdlib.h>
#include <stddef.h>

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
  lista_t* lista;
  nodo_t* actual;
  nodo_t* anterior;
};

nodo_t* crear_nodo(void* dato, nodo_t* proximo) {
  nodo_t* nodo_nuevo = malloc(sizeof(nodo_t));
  if(!nodo_nuevo) return NULL;

  nodo_nuevo->dato = dato;
  nodo_nuevo->proximo = proximo;
  return nodo_nuevo;
}

/* ******************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/

lista_t* lista_crear() {
  lista_t* lista = malloc(sizeof(lista_t));
  if(!lista) return NULL;

  lista->primero = NULL;
  lista->ultimo = NULL;
  lista->largo = 0;

  return lista;
}

bool lista_esta_vacia(const lista_t* lista) {
  if(!lista) return false;
  return (lista->primero == NULL && lista->ultimo == NULL && lista->largo == 0);
}

bool lista_insertar_primero(lista_t *lista, void *dato) {
  nodo_t* nodo_nuevo = crear_nodo(dato, lista->primero);
  if(!nodo_nuevo) return false;

  if(lista_esta_vacia(lista)) lista->ultimo = nodo_nuevo;
  lista->primero = nodo_nuevo;
  lista->largo++;

  return true;
}

bool lista_insertar_ultimo(lista_t *lista, void *dato) {
  nodo_t* nodo_nuevo = crear_nodo(dato, NULL);
  if(!nodo_nuevo) return false;

  if(lista_esta_vacia(lista)) lista->primero = nodo_nuevo;
  else lista->ultimo->proximo = nodo_nuevo;
  lista->ultimo = nodo_nuevo;
  lista->largo++;

  return true;
}

void *lista_borrar_primero(lista_t *lista) {
  if(lista_esta_vacia(lista)) return NULL;

  void* dato_primero = lista_ver_primero(lista);
  nodo_t* nodo_primero = lista->primero;

  lista->primero = nodo_primero->proximo;
  if(lista_largo(lista) == 1) lista->ultimo = NULL;
  lista->largo--;

  free(nodo_primero);
  return dato_primero;
}

void *lista_ver_primero(const lista_t *lista) {
  return lista_esta_vacia(lista)? NULL : lista->primero->dato;
}

void *lista_ver_ultimo(const lista_t* lista) {
  return lista_esta_vacia(lista)? NULL : lista->ultimo->dato;
}

size_t lista_largo(const lista_t *lista) {
  return lista->largo;
}

void lista_destruir(lista_t *lista, void destruir_dato(void *)) {
  while(!lista_esta_vacia(lista)) {
    if(destruir_dato) destruir_dato(lista_borrar_primero(lista));
    else lista_borrar_primero(lista);
  }
  free(lista);
}

/* ******************************************************************
 *                 PRIMITIVAS DEL ITERADOR INTERNO
 * *****************************************************************/

void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra){
  if(visitar != NULL) {
    nodo_t* actual = lista->primero;
    while(actual) {
      if(!visitar(actual->dato, extra)) return;
      actual = actual->proximo;
    }
  }
 }

/* ******************************************************************
 *                 PRIMITIVAS DEL ITERADOR EXTERNO
 * *****************************************************************/

 lista_iter_t *lista_iter_crear(lista_t *lista) {
   lista_iter_t* iter = malloc(sizeof(lista_iter_t));
   if(!iter) return NULL;

   iter->actual = lista->primero;
   iter->anterior = NULL;
   iter->lista = lista;

   return iter;
 }

 bool lista_iter_avanzar(lista_iter_t *iter) {
   if(lista_iter_al_final(iter)) return false;

   iter->anterior = iter->actual;
   iter->actual = iter->actual->proximo;

   return true;
 }

void *lista_iter_ver_actual(const lista_iter_t *iter) {
  return iter->actual == NULL ? NULL : iter->actual->dato;
}

bool lista_iter_al_final(const lista_iter_t *iter) {
  return iter->actual == NULL;
}

void lista_iter_destruir(lista_iter_t *iter) {
  free(iter);
}

bool lista_iter_insertar(lista_iter_t *iter, void *dato) {
  nodo_t* nodo_nuevo = crear_nodo(dato, iter->actual);
  if(!nodo_nuevo) return false;

  if(lista_iter_al_final(iter)) iter->lista->ultimo = nodo_nuevo;
  if(iter->actual == iter->lista->primero) iter->lista->primero = nodo_nuevo;
  if(iter->anterior) iter->anterior->proximo = nodo_nuevo;
  iter->actual = nodo_nuevo;
  iter->lista->largo++;

  return true;
}

void *lista_iter_borrar(lista_iter_t *iter) {
  if(lista_iter_al_final(iter)) return NULL;

  if(iter->anterior) iter->anterior->proximo = iter->actual->proximo;
  if(iter->actual == iter->lista->ultimo) iter->lista->ultimo = iter->anterior;
  if(iter->actual == iter->lista->primero) iter->lista->primero = iter->actual->proximo;
  iter->lista->largo--;
  nodo_t* actual = iter->actual;
  void* dato_actual = actual->dato;
  iter->actual = actual->proximo;
  free(actual);

  return dato_actual;
}

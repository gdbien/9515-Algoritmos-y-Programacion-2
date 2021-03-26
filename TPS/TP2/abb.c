#define _GNU_SOURCE 1
#include <stdlib.h>
#include <string.h>
#include "abb.h"
#include "pila.h"

typedef struct abb_nodo {
  struct abb_nodo* izq;
  struct abb_nodo* der;
  char* clave;
  void* dato;
} abb_nodo_t;

struct abb {
  abb_nodo_t* raiz;
  abb_comparar_clave_t claves_cmp;
  abb_destruir_dato_t destruir_dato;
  size_t cantidad;
};

struct abb_iter {
  abb_t* arbol;
  pila_t* pila;
};

// Pre: Recibe una clave y un dato
// Post: Crea un nodo con el par clave-dato.
abb_nodo_t* nodo_crear(const char* clave, void* dato) {
  abb_nodo_t* nodo = malloc(sizeof(abb_nodo_t));
  nodo->izq = NULL;
  nodo->der = NULL;
  nodo->dato = dato;
  nodo->clave = strdup(clave);
  if(!nodo->clave) {
    free(nodo);
    return NULL;
  }
  return nodo;
}

bool nodo_insertar(abb_nodo_t* nodo_actual, abb_nodo_t* nodo_nuevo, abb_comparar_clave_t claves_cmp) {
  if(claves_cmp(nodo_actual->clave, nodo_nuevo->clave) > 0) {
    if(!nodo_actual->izq) nodo_actual->izq = nodo_nuevo;
    else nodo_insertar(nodo_actual->izq, nodo_nuevo, claves_cmp);
  }
  else {
    if(!nodo_actual->der) nodo_actual->der = nodo_nuevo;
    else nodo_insertar(nodo_actual->der, nodo_nuevo, claves_cmp);
  }
  return true;
}

// Pre: Recibe un nodo.
// Post: Destruye el nodo en su totalidad.
void nodo_destruir(abb_nodo_t* nodo, abb_destruir_dato_t destruir_dato) {
  if(destruir_dato) destruir_dato(nodo->dato);
  free(nodo->clave);
  free(nodo);
}

void abb_nodo_destruir(abb_nodo_t* nodo_actual, abb_destruir_dato_t destruir_dato) {
  if(nodo_actual) {
    abb_nodo_destruir(nodo_actual->izq, destruir_dato);
    abb_nodo_destruir(nodo_actual->der, destruir_dato);
    nodo_destruir(nodo_actual,destruir_dato);
  }
}

bool nodo_in_order(abb_nodo_t* nodo_actual, bool visitar(const char *, void *, void *), void *extra) {
  if(!nodo_actual) return true;
  if(!nodo_in_order(nodo_actual->izq, visitar, extra)) return false;
  if(!visitar(nodo_actual->clave, nodo_actual->dato, extra)) return false;
  if(!nodo_in_order(nodo_actual->der, visitar, extra)) return false;
  return true;
}

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato) {
  abb_t* abb = malloc(sizeof(abb_t));
  if(!abb) return NULL;
  abb->raiz = NULL;
  abb->claves_cmp = cmp;
  abb->destruir_dato = destruir_dato;
  abb->cantidad = 0;
  return abb;
}

size_t abb_cantidad(abb_t *arbol) {
  return arbol->cantidad;
}

// Post: Busca el nodo que le corresponde a la clave, y lo devuelve, si la clave no existe, devuelve NULL.
abb_nodo_t* nodo_buscar(abb_nodo_t* nodo, const char* clave, abb_comparar_clave_t claves_cmp) {
  if(nodo) {
    if(claves_cmp(nodo->clave,clave) == 0) return nodo;
    if(claves_cmp(nodo->clave,clave) < 0) {
      return nodo_buscar(nodo->der,clave,claves_cmp);
    }
    else {
      return nodo_buscar(nodo->izq,clave,claves_cmp);
    }
  }
  return NULL;
}

bool abb_guardar(abb_t *arbol, const char *clave, void *dato) {
  abb_nodo_t* nodo = nodo_buscar(arbol->raiz, clave, arbol->claves_cmp);
  if(!nodo) {
    abb_nodo_t* nodo_nuevo = nodo_crear(clave, dato);
    if(!arbol->raiz) arbol->raiz = nodo_nuevo;
    else nodo_insertar(arbol->raiz, nodo_nuevo, arbol->claves_cmp);
    arbol->cantidad++;
  }
  else {
    if(arbol->destruir_dato) arbol->destruir_dato(nodo->dato);
    nodo->dato = dato;
  }
  return true;
}

bool abb_pertenece(const abb_t* arbol, const char *clave) {
  return nodo_buscar(arbol->raiz,clave,arbol->claves_cmp) ? true : false;
}

void *abb_obtener(const abb_t *arbol, const char *clave) {
  abb_nodo_t* nodo = nodo_buscar(arbol->raiz,clave,arbol->claves_cmp);
  if(nodo) return nodo->dato;
  return NULL;
}

void abb_destruir(abb_t *arbol) {
  abb_nodo_destruir(arbol->raiz, arbol->destruir_dato);
  free(arbol);
}



/******************** ITERADOR INTERNO ********************/

void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra) {
  if(!visitar) return;
  nodo_in_order(arbol->raiz, visitar, extra);
}

/******************** ITERADOR EXTERNO ********************/

abb_iter_t *abb_iter_in_crear(const abb_t *arbol) {
  abb_iter_t* iter = malloc(sizeof(abb_iter_t));
  if(!iter) return NULL;
  iter->arbol = (abb_t*) arbol;
  iter->pila = pila_crear();
  if(!iter->pila) {
    free(iter);
    return NULL;
  }
  abb_nodo_t* actual = arbol->raiz;
  while(actual) {
    pila_apilar(iter->pila, actual);
    actual = actual->izq;
  }
  return iter;
}

bool abb_iter_in_avanzar(abb_iter_t *iter) {
  if(abb_iter_in_al_final(iter)) return false;
  abb_nodo_t* actual = ((abb_nodo_t*)pila_desapilar(iter->pila))->der;
  while(actual) {
    pila_apilar(iter->pila, actual);
    actual = actual->izq;
  }
  return true;
}

bool abb_iter_in_al_final(const abb_iter_t *iter) {
  return pila_esta_vacia(iter->pila);
}

const char *abb_iter_in_ver_actual(const abb_iter_t *iter) {
  if(abb_iter_in_al_final(iter)) return NULL;
  return ((abb_nodo_t*)pila_ver_tope(iter->pila))->clave;
}

void abb_iter_in_destruir(abb_iter_t* iter) {
  pila_destruir(iter->pila);
  free(iter);
}
// Pre: Recibe un nodo del arbol.
// Post: Busca el nodo padre del nodo recibido, y lo devuelve.
abb_nodo_t* padre_buscar(abb_nodo_t* nodo_actual, abb_nodo_t* nodo_padre, const char* clave, abb_comparar_clave_t claves_cmp) {
  if(claves_cmp(nodo_actual->clave,clave) == 0) return nodo_padre;
  if(claves_cmp(nodo_actual->clave,clave) < 0) {
    if(nodo_actual->der) {
      nodo_padre = nodo_actual;
      return padre_buscar(nodo_actual->der,nodo_padre,clave,claves_cmp);
    }
    else return NULL;
  }
  else {
    if(nodo_actual->izq) {
      nodo_padre = nodo_actual;
      return padre_buscar(nodo_actual->izq,nodo_padre,clave,claves_cmp);
    }
    else return NULL;
  }
}

// Pre: Recibe un nodo.
// Post: Busca el menor nodo del nodo recibido, y lo devuelve.
abb_nodo_t* abb_nodo_minimo(abb_nodo_t* nodo) {
  abb_nodo_t* nodo_actual = nodo;
  while(nodo_actual->izq) nodo_actual = nodo_actual->izq;
  return nodo_actual;
}

void* nodo_borrar(abb_nodo_t* borrado, abb_t* arbol, abb_nodo_t* padre) {
  void* dato = borrado->dato;
  if(!borrado->izq && !borrado->der) {
    if(borrado == arbol->raiz) arbol->raiz = NULL;
    else {
      if(borrado == padre->izq) padre->izq = NULL;
      else padre->der = NULL;
    }
    nodo_destruir(borrado, NULL);
  }
  else if(!borrado->der) {
    abb_nodo_t* nodo_aux = borrado;
    if(!padre) arbol->raiz = borrado->izq;
    else if(borrado == padre->izq) padre->izq = borrado->izq;
    else padre->der = borrado->izq;
    nodo_destruir(nodo_aux, NULL);
  }
  else if(!borrado->izq) {
    abb_nodo_t* nodo_aux = borrado;
    if(!padre) arbol->raiz = borrado->der;
    else if(borrado == padre->izq) padre->izq = borrado->der;
    else padre->der = borrado->der;
    nodo_destruir(nodo_aux, NULL);
  }
  else if(borrado->izq && borrado->der) {
    abb_nodo_t* sucesor = abb_nodo_minimo(borrado->der);
    abb_nodo_t* aux = NULL;
    abb_nodo_t* nodo_father = padre_buscar(arbol->raiz,aux,sucesor->clave,arbol->claves_cmp);
    free(borrado->clave);
    borrado->dato = sucesor->dato;
    borrado->clave = strdup(sucesor->clave);
    nodo_borrar(sucesor,arbol,nodo_father);
  }
  return dato;
}

void* abb_borrar(abb_t *arbol, const char *clave) {
  if(!arbol->raiz) return NULL;
  abb_nodo_t* nodo = nodo_buscar(arbol->raiz,clave,arbol->claves_cmp);
  if(!nodo) return NULL;
  abb_nodo_t* aux = NULL;
  abb_nodo_t* nodo_padre = padre_buscar(arbol->raiz,aux,clave,arbol->claves_cmp);
  arbol->cantidad--;
  return nodo_borrar(nodo,arbol,nodo_padre);
}

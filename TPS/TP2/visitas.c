#include <stdbool.h>
#include <stdio.h>
#include "abb.h"
#include "heap.h"
#include "pila.h"
#include "strutil.h"
#include "visitas.h"
#include "hash.h"
#include "ip.h"

#define CMP_IGUAL 0
#define CMP_MENOR -1
#define CMP_MAYOR 1

struct visitantes {
  abb_t* abb;
  hash_t* hash;
};

typedef struct rango {
  char* desde;
  char* hasta;
} rango_t;

typedef struct sitio {
  const char* nombre;
  size_t visitas;
} sitio_t;

rango_t* rango_crear(char* desde, char* hasta);
void sitio_destruir(sitio_t* sitio);
void wrapper_sitio_destruir(void* dato);
pila_t* crear_pila_mas_visitados(hash_t* hash_sitios, size_t cantidad);
bool imprimir_visitantes(const char* clave, void* dato, void* extra);

/******************** PRIMITIVAS VISITAS ********************/

visitantes_t* visitantes_crear() {
  visitantes_t* visitantes = malloc(sizeof(visitantes_t));
  if(!visitantes) return NULL;
  abb_t* abb = abb_crear(cmp_ip, NULL);
  if(!abb) {
    free(visitantes);
    return NULL;
  }
  hash_t* hash = hash_crear(free);
  if(!hash) {
    free(visitantes);
    abb_destruir(abb);
    return NULL;
  }
  visitantes->abb = abb;
  visitantes->hash = hash;
  return visitantes;
}

void visitantes_destruir(visitantes_t* visitantes) {
  abb_destruir(visitantes->abb);
  hash_destruir(visitantes->hash);
  free(visitantes);
}

bool agregar_visitante(visitantes_t* visitantes, const char* ip_nuevo, char* sitio) {
  size_t* cantidad_visitas = hash_obtener(visitantes->hash, sitio);
  if(!cantidad_visitas) {
    cantidad_visitas = malloc(sizeof(size_t));
    if(!cantidad_visitas) return false;
    (*cantidad_visitas) = 1;
    if(!hash_guardar(visitantes->hash, sitio, cantidad_visitas)) {
      free(cantidad_visitas);
      return false;
    }
  }
  else (*cantidad_visitas)++;
  if(!abb_guardar(visitantes->abb, ip_nuevo, NULL)) {
    free(cantidad_visitas);
    return false;
  }
  return true;
}

bool imprimir_mas_visitados(visitantes_t* visitantes, size_t cantidad) {
  pila_t* sitios_p = crear_pila_mas_visitados(visitantes->hash, cantidad);
  if(!sitios_p) return false;
  while(!pila_esta_vacia(sitios_p)) {
    sitio_t* sitio = pila_desapilar(sitios_p);
    printf("\t%s - %zu\n", sitio->nombre, sitio->visitas);
    sitio_destruir(sitio);
  }
  pila_destruir(sitios_p);
  return true;
}

bool imprimir_visitantes_desde_hasta(visitantes_t* visitantes, char* desde, char* hasta) {
  rango_t* rango = rango_crear(desde, hasta);
  if(!rango) return false;
  abb_in_order(visitantes->abb, imprimir_visitantes, rango);
  free(rango);
  return true;
}

/******************** FUNCIONES AUXILIARES ********************/

rango_t* rango_crear(char* desde, char* hasta) {
  rango_t* rango = malloc(sizeof(rango_t));
  if(!rango) return NULL;
  rango->desde = desde;
  rango->hasta = hasta;
  return rango;
}

int cmp_sitios_min(const sitio_t* s1, const sitio_t* s2) {
  if(s1->visitas > s2->visitas) return CMP_MENOR;
  if(s1->visitas < s2->visitas) return CMP_MAYOR;
  return CMP_IGUAL;
}

int cmp_sitios_max(const sitio_t* s1, const sitio_t* s2) {
  if(s1->visitas > s2->visitas) return CMP_MAYOR;
  if(s1->visitas < s2->visitas) return CMP_MENOR;
  return CMP_IGUAL;
}

int wrapper_cmp_sitios_min(const void* a, const void* b) {
  const sitio_t* s1 = a;
  const sitio_t* s2 = b;
  return cmp_sitios_min(s1, s2);
}

sitio_t* sitio_crear(const char* nombre, size_t visitas) {
  sitio_t* sitio = malloc(sizeof(sitio_t));
  if(!sitio) return NULL;
  sitio->nombre = nombre;
  sitio->visitas = visitas;
  return sitio;
}

sitio_t* sitio_obtener_actual(hash_t* hash_sitios, hash_iter_t* iter) {
  const char* sitio_nombre = hash_iter_ver_actual(iter);
  size_t sitio_visitas = *(size_t*)hash_obtener(hash_sitios, sitio_nombre);
  sitio_t* sitio = sitio_crear(sitio_nombre, sitio_visitas);
  return sitio;
}

void sitio_destruir(sitio_t* sitio) {
  free(sitio);
}

void wrapper_sitio_destruir(void* dato) {
  sitio_t* sitio = dato;
  sitio_destruir(sitio);
}

bool heap_encolar_n_sitios(hash_iter_t* iter, hash_t* hash_sitios, heap_t* mas_visitados, size_t cantidad) {
  size_t i = 0;
  while(!hash_iter_al_final(iter) && i < cantidad) {
    sitio_t* sitio = sitio_obtener_actual(hash_sitios, iter);
    if(!sitio) return false;
    heap_encolar(mas_visitados, sitio);
    hash_iter_avanzar(iter);
    i++;
  }
  return true;
}

heap_t* crear_heap_mas_visitados(hash_t* hash_sitios, size_t cantidad) {
  hash_iter_t* iter = hash_iter_crear(hash_sitios);
  if(!iter) return NULL;
  heap_t* mas_visitados = heap_crear(wrapper_cmp_sitios_min);
  if(!mas_visitados) {
    hash_iter_destruir(iter);
    return NULL;
  }
  if(!heap_encolar_n_sitios(iter, hash_sitios, mas_visitados, cantidad)) {
    heap_destruir(mas_visitados, wrapper_sitio_destruir);
    hash_iter_destruir(iter);
  }
  while(!hash_iter_al_final(iter)) {
    sitio_t* sitio = sitio_obtener_actual(hash_sitios, iter);
    if(!sitio) {
      heap_destruir(mas_visitados, wrapper_sitio_destruir);
      hash_iter_destruir(iter);
    }
    if(cmp_sitios_max(sitio, (sitio_t*)heap_ver_max(mas_visitados)) > 0) {
      sitio_destruir(heap_desencolar(mas_visitados));
      heap_encolar(mas_visitados, sitio);
    } else {
      sitio_destruir(sitio);
    }
    hash_iter_avanzar(iter);
  }
  hash_iter_destruir(iter);
  return mas_visitados;
}

pila_t* crear_pila_mas_visitados(hash_t* hash_sitios, size_t cantidad) {
  heap_t* heap_mas_visitados = crear_heap_mas_visitados(hash_sitios, cantidad);
  if(!heap_mas_visitados) return NULL;
  pila_t* pila_mas_visitados = pila_crear();
  if(!pila_mas_visitados) {
    heap_destruir(heap_mas_visitados, NULL);
    return NULL;
  }
  while(!heap_esta_vacio(heap_mas_visitados)) {
    sitio_t* sitio = (sitio_t*)heap_desencolar(heap_mas_visitados);
    pila_apilar(pila_mas_visitados, sitio);
  }
  heap_destruir(heap_mas_visitados, NULL);
  return pila_mas_visitados;
}

bool imprimir_visitantes(const char* clave, void* dato, void* extra) {
  rango_t* rango = extra;
  if(cmp_ip(clave, rango->hasta) > 0) return false;
  if(cmp_ip(clave, rango->desde) >= 0) printf("\t%s\n", clave);
  return true;
}

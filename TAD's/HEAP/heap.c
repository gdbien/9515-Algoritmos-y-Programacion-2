#include <stdlib.h>
#include "heap.h"

#define TAM_INICIAL 10

struct heap {
  cmp_func_t cmp;
  void** arr;
  size_t cant;
  size_t tam;
};

void swap(void** array, size_t pos1, size_t pos2) {
  void* aux = array[pos1];
  array[pos1] = array[pos2];
  array[pos2] = aux;
}

int obtener_pos_padre(size_t pos_hijo) {
  return (int)(pos_hijo-1)/2;
}

int obtener_pos_hijo_izq(size_t pos_padre) {
  return (int)(2*pos_padre)+1;
}

int obtener_pos_hijo_der(size_t pos_padre) {
  return (int)(2*pos_padre)+2;
}

void arr_cpy(void** arr_original, void** arr_copia, size_t tam) {
  for(size_t i = 0; i < tam; i++) {
    arr_copia[i] = arr_original[i];
  }
}

size_t pos_mayor(heap_t* heap, size_t pos1, size_t pos2) {
  if(heap->cmp(heap->arr[pos1], heap->arr[pos2]) < 0) return pos2;
  return pos1;
}

void downheap_x(heap_t* heap, size_t pos) {
  int pos_hijo_der = obtener_pos_hijo_der(pos);
  int pos_hijo_izq = obtener_pos_hijo_izq(pos);
  if(pos_hijo_der >= heap->cant && pos_hijo_izq < heap->cant) {
    if(heap->cmp(heap->arr[pos], heap->arr[pos_hijo_izq]) < 0) {
      swap(heap->arr, pos, pos_hijo_izq);
      downheap_x(heap, pos_hijo_izq);
    }
  }
  else if(pos_hijo_der < heap->cant && pos_hijo_izq < heap->cant) {
    if(heap->cmp(heap->arr[pos], heap->arr[pos_hijo_izq]) < 0 || heap->cmp(heap->arr[pos], heap->arr[pos_hijo_der]) < 0) {
      size_t pos_hijo_mayor = pos_mayor(heap, pos_hijo_der, pos_hijo_izq);
      swap(heap->arr, pos, pos_hijo_mayor);
      downheap_x(heap, pos_hijo_mayor);
    }
  }
}

void downheap(heap_t* heap) {
  downheap_x(heap, 0);
}

void heap_destruir(heap_t *heap, void destruir_elemento(void *e)) {
  if(destruir_elemento) {
    for(size_t i = 0; i < heap->cant; i++) {
      destruir_elemento(heap->arr[i]);
    }
  }
  free(heap->arr);
  free(heap);
}

bool redimensionar_heap(heap_t* heap, size_t tam_nuevo) {
  void** arr_nuevo = malloc(tam_nuevo*sizeof(void*));
  if(!arr_nuevo) return false;
  arr_cpy(heap->arr, arr_nuevo, heap->cant);
  free(heap->arr);
  heap->tam = tam_nuevo;
  heap->arr = arr_nuevo;
  return true;
}

heap_t* heap_crear_con_tam(cmp_func_t cmp, size_t tam) {
  heap_t* heap = malloc(sizeof(heap_t));
  if(!heap) return NULL;
  heap->cmp = cmp;
  heap->cant = 0;
  heap->tam = tam;
  heap->arr = malloc(tam*sizeof(void*));
  if(!heap->arr) {
    free(heap);
    return NULL;
  }
  return heap;
}

void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp) {
  heap_t* heap = heap_crear_arr(elementos, cant, cmp);
  if(!heap) return;
  while(heap->cant > 0) {
    swap(heap->arr, 0, heap->cant-1);
    heap->cant--;
    downheap(heap);
  }
  arr_cpy(heap->arr, elementos, cant);
  heap_destruir(heap, NULL);
}

heap_t *heap_crear(cmp_func_t cmp) {
  heap_t* heap = heap_crear_con_tam(cmp, TAM_INICIAL);
  if(!heap) return NULL;
  return heap;
}

heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp) {
  heap_t* heap = heap_crear_con_tam(cmp, n);
  if(!heap) return NULL;
  arr_cpy(arreglo, heap->arr, n);
  heap->cant = n;
  for(int i = (int)(heap->cant-1)/2; i >= 0; i--) {
    downheap_x(heap, i);
  }
  return heap;
}

void upheap_x(heap_t* heap, size_t pos) {
  int pos_padre = obtener_pos_padre(pos);
  if(pos_padre < 0) return;
  if(heap->cmp(heap->arr[pos], heap->arr[pos_padre]) > 0) {
    swap(heap->arr, pos, pos_padre);
    upheap_x(heap, pos_padre);
  }
}

void upheap(heap_t* heap) {
  upheap_x(heap, heap->cant);
}

bool heap_encolar(heap_t *heap, void *elem) {
  if(heap->cant >= heap->tam) redimensionar_heap(heap, heap->tam*2);
  heap->arr[heap->cant] = elem;
  upheap(heap);
  heap->cant++;
  return true;
}

size_t heap_cantidad(const heap_t *heap) {
  return heap->cant;
}

bool heap_esta_vacio(const heap_t *heap) {
  return heap->cant == 0;
}

void *heap_desencolar(heap_t *heap) {
  if(heap_esta_vacio(heap)) return NULL;
  void* desencolado = heap->arr[0];
  heap->cant--;
  swap(heap->arr, 0, heap->cant);
  downheap(heap);
  if(heap->cant <= heap->tam/4 && heap->tam > TAM_INICIAL) redimensionar_heap(heap, heap->tam/2);
  return desencolado;
}

void *heap_ver_max(const heap_t *heap) {
  return heap_esta_vacio(heap) ? NULL : heap->arr[0];
}

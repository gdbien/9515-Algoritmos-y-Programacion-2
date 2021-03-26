#include <time.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "testing.h"
#include "heap.h"

#define ANSI_COLOR_LGH_RED     "\x1b[1m\x1b[31m"
#define ANSI_COLOR_LGH_GREEN   "\x1b[1m\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define TAM 100

int comparar_int(const int* numero1, const int* numero2) {
  if(*numero1 < *numero2) return -1;
  if(*numero1 == *numero2) return 0;
  else return 1;
}

int wrapper_comparar_int(const void* a, const void* b) {
  const int* n1 = a;
  const int* n2 = b;
  return comparar_int(n1, n2);
}

void imprimir_arr_int(int** array, int tam) {
  for(int i = 0; i < tam; i++) {
    printf("%d |", *(array[i]));
  }
  printf("\n");
}

int wrapper_strcmp(const void* a, const void* b) {
  char* str1 = (char*)a;
  char* str2 = (char*)b;
  return strcmp(str1, str2);
}

void swap_func(void** array, size_t pos1, size_t pos2) {
  void* aux = array[pos1];
  array[pos1] = array[pos2];
  array[pos2] = aux;
}

bool arr_cmp_iguales(void** arr1, void** arr2, int largo) {
  for(int i=0; i < largo; i++) {
    if(wrapper_comparar_int(arr1[i],arr2[i]) != 0) return false;
  }
  return true;
}

void pruebas_heap_vacio() {
  printf("\n---- INICIO PRUEBAS HEAP VACIO ----\n\n");

  heap_t* heap = heap_crear(wrapper_strcmp);
  print_test("Se pudo crear el heap", heap);

  print_test("El heap está vacío", heap_esta_vacio(heap));
  print_test("Cantidad es 0", heap_cantidad(heap) == 0);
  print_test("Ver max devuelve NULL", !heap_ver_max(heap));
  print_test("Desencolar devuelve NULL", !heap_desencolar(heap));

  heap_destruir(heap, NULL);
  print_test("Se destruyó el heap", true);
}

void pruebas_heap_encolar() {
  printf("\n---- INICIO HEAP ENCOLAR ----\n\n");

  heap_t* heap = heap_crear(wrapper_strcmp);
  print_test("Se pudo crear el heap", heap);

  char* alpha = "a";
  char* beta = "b";
  char* gamma = "g";

  print_test("Se encoló: alpha", heap_encolar(heap, alpha));
  print_test("Cantidad es 1", heap_cantidad(heap) == 1);
  print_test("El heap no está vacío", !heap_esta_vacio(heap));
  print_test("El máximo es el encolado: alpha", strcmp(heap_ver_max(heap), alpha) == 0);
  print_test("Se encoló: gamma", heap_encolar(heap, gamma));
  print_test("Cantidad es 2", heap_cantidad(heap) == 2);
  print_test("El heap no está vacío", !heap_esta_vacio(heap));
  print_test("El máximo cambió: gamma", strcmp(heap_ver_max(heap), gamma) == 0);
  print_test("Se encoló: beta", heap_encolar(heap, beta));
  print_test("Cantidad es 3", heap_cantidad(heap) == 3);
  print_test("El heap no está vacío", !heap_esta_vacio(heap));
  print_test("El máximo se mantuvo: gamma", strcmp(heap_ver_max(heap), gamma) == 0);

  heap_destruir(heap, NULL);
  print_test("Se destruyó el heap", true);
}

void pruebas_heap_desencolar() {
  printf("\n---- INICIO PRUEBAS HEAP DESENCOLAR ----\n\n");

  heap_t* heap = heap_crear(wrapper_strcmp);
  print_test("Se pudo crear el heap", heap);

  char* alpha = "a";
  char* beta = "b";
  char* gamma = "g";

  print_test("Se encoló: alpha", heap_encolar(heap, alpha));
  print_test("Cantidad es 1", heap_cantidad(heap) == 1);
  print_test("Se encoló: gamma", heap_encolar(heap, gamma));
  print_test("Cantidad es 2", heap_cantidad(heap) == 2);
  print_test("Se encoló: beta", heap_encolar(heap, beta));
  print_test("Cantidad es 3", heap_cantidad(heap) == 3);

  print_test("El máximo es: gamma", strcmp(heap_ver_max(heap), gamma) == 0);
  print_test("Desencolar devuelve el máximo: gamma", strcmp(heap_desencolar(heap), gamma) == 0);
  print_test("Cantidad es 2", heap_cantidad(heap) == 2);
  print_test("El heap no está vacío", !heap_esta_vacio(heap));
  print_test("El máximo es: beta", strcmp(heap_ver_max(heap), beta) == 0);
  print_test("Desencolar devuelve el máximo: beta", strcmp(heap_desencolar(heap), beta) == 0);
  print_test("Cantidad es 1", heap_cantidad(heap) == 1);
  print_test("El heap no está vacío", !heap_esta_vacio(heap));
  print_test("El máximo es: alpha", strcmp(heap_ver_max(heap), alpha) == 0);
  print_test("Desencolar devuelve el máximo: alpha", strcmp(heap_desencolar(heap), alpha) == 0);
  print_test("Cantidad es 0", heap_cantidad(heap) == 0);
  print_test("El hesp está vacío", heap_esta_vacio(heap));
  print_test("Ver máximo en heap vacío devuelve NULL", !heap_ver_max(heap));
  print_test("Desencolar en heap vacío devuelve NULL", !heap_desencolar(heap));

  heap_destruir(heap, NULL);
  print_test("Se destruyó el heap", true);
}

void pruebas_heap_encolar_con_destruir() {
  printf("\n---- INICIO PRUEBAS HEAP ENCOLAR CON DESTRUIR ----\n\n");

  heap_t* heap = heap_crear(wrapper_strcmp);
  print_test("Se pudo crear el heap", heap);

  char* alpha = malloc(sizeof(char)*2);
  char* beta = malloc(sizeof(char)*2);
  char* gamma = malloc(sizeof(char)*2);
  strcpy(alpha, "a");
  strcpy(beta, "b");
  strcpy(gamma, "g");

  print_test("Se encoló: alpha", heap_encolar(heap, alpha));
  print_test("Cantidad es 1", heap_cantidad(heap) == 1);
  print_test("Se encoló: gamma", heap_encolar(heap, gamma));
  print_test("Cantidad es 2", heap_cantidad(heap) == 2);
  print_test("Se encoló: beta", heap_encolar(heap, beta));
  print_test("Cantidad es 3", heap_cantidad(heap) == 3);

  heap_destruir(heap, free);
  print_test("Se destruyó el heap", true);

}

void pruebas_heap_encolar_desencolar() {
  printf("\n---- INICIO PRUEBAS HEAP ENCOLAR DESENCOLAR MISMO ELEMENTO ----\n\n");

  heap_t* heap = heap_crear(wrapper_strcmp);
  print_test("Se pudo crear el heap", heap);

  char* alpha = "a";

  print_test("Se encoló: alpha", heap_encolar(heap, alpha));
  print_test("Cantidad es 1", heap_cantidad(heap) == 1);
  print_test("Se desencoló máximo: alpha", strcmp(heap_desencolar(heap), alpha) == 0);
  print_test("Cantidad es 0", heap_cantidad(heap) == 0);
  print_test("El heap está vacío", heap_esta_vacio(heap));
  print_test("Se encoló: alpha", heap_encolar(heap, alpha));
  print_test("Cantidad es 1", heap_cantidad(heap) == 1);

  heap_destruir(heap, NULL);
  print_test("Se destruyó el heap", heap);
}

void pruebas_heap_encolar_int() {
  printf("\n---- INICIO HEAP ENCOLAR INTS ----\n\n");

  heap_t* heap = heap_crear(wrapper_comparar_int);
  print_test("Se pudo crear el heap", heap);

  int uno = 1;
  int cincuenta = 50;
  int tres = 3;
  int cincuentados = 52;

  print_test("Se encoló: 1", heap_encolar(heap, &uno));
  print_test("Cantidad es 1", heap_cantidad(heap) == 1);
  print_test("El heap no está vacío", !heap_esta_vacio(heap));
  print_test("El máximo es el encolado: 1", *((int*)heap_ver_max(heap))==uno);
  print_test("Se encoló: 50", heap_encolar(heap, &cincuenta));
  print_test("Cantidad es 2", heap_cantidad(heap) == 2);
  print_test("El heap no está vacío", !heap_esta_vacio(heap));
  print_test("El máximo cambió: 50", *((int*)heap_ver_max(heap))==cincuenta);
  print_test("Se encoló: 3", heap_encolar(heap, &tres));
  print_test("Cantidad es 3", heap_cantidad(heap) == 3);
  print_test("El heap no está vacío", !heap_esta_vacio(heap));
  print_test("El máximo se mantuvo: 50", *((int*)heap_ver_max(heap))==cincuenta);
  print_test("Se encoló: 52", heap_encolar(heap, &cincuentados));
  print_test("Cantidad es 4", heap_cantidad(heap) == 4);
  print_test("El heap no está vacío", !heap_esta_vacio(heap));
  print_test("El máximo cambio: 52", *((int*)heap_ver_max(heap))==cincuentados);

  heap_destruir(heap, NULL);
  print_test("Se destruyó el heap", true);
}

void prueba_heap_sort(int largo) {
  printf("\n---- INICIO PRUEBAS HEAPSORT VECTOR CON 'LARGO' ELEMENTOS ----\n\n");

  int* valores[largo];
  int* valores_copia[largo];

  for(int i = 0; i < largo; i++) {
    valores[i] = malloc(sizeof(int));
    valores_copia[i] = malloc(sizeof(int));
    *valores[i] = i;
    *valores_copia[i] = i;
  }
  print_test("Se creó el vector original", valores!=NULL);
  imprimir_arr_int(valores, largo);
  print_test("Se creó el vector copia", valores_copia!=NULL);
  imprimir_arr_int(valores_copia, largo);

  srand((unsigned int) time(NULL));

  // Mezclamos el array: algoritmo de Fisher–Yates
  for(int i = (int) (largo - 1); i >= 0; i--) {
    unsigned int j = rand() % (i+1);
    swap_func((void**) valores_copia, i, j);  
  }
  print_test("Se mezcló el vector copia", true);
  imprimir_arr_int(valores_copia, largo);

  heap_sort((void**)valores_copia, largo, *wrapper_comparar_int);
  print_test("Se aplico heap sort al arreglo desordenado", true);

  print_test("El arreglo copia esta ordenado", arr_cmp_iguales((void**)valores,(void**)valores_copia,largo));
  imprimir_arr_int(valores_copia, largo);
  
  for(int i = 0; i < largo; i++) {
    free(valores[i]);
    free(valores_copia[i]);
  }
}


void pruebas_heap_volumen(int largo) {
  printf("\n---- INICIO PRUEBAS HEAP VOLUMEN ----\n\n");

  heap_t* heap = heap_crear(wrapper_comparar_int);
  print_test("Se creó el heap", heap);

  int* valores[largo];

  bool encolo_ok = true, ver_max_ok = true;
  for(int i = 0; i < largo; i++) {
    valores[i] = malloc(sizeof(int));
    *valores[i] = i;
    encolo_ok &= heap_encolar(heap, valores[i]);
    ver_max_ok &= (*(int*)heap_ver_max(heap) == i);
  }

  print_test("Encolar muchos elementos", encolo_ok);
  print_test("La cantidad es correcta", heap_cantidad(heap) == largo);
  print_test("Ver máximo devuelve el valor correcto", ver_max_ok);

  bool desencolo_ok = true;
  for(int i = largo-1; i >= 0; i--) {
    desencolo_ok &= (*(int*)heap_desencolar(heap) == *valores[i]);
  }

  print_test("Desencolar muchos elementos", desencolo_ok);
  print_test("El heap está vacío", heap_esta_vacio(heap));
  print_test("Cantidad es 0", heap_cantidad(heap) == 0);
  print_test("Ver máximo en heap vacío devuelve NULL", !heap_ver_max(heap));
  print_test("Desencolar en heap vacío devuelve NULL", !heap_desencolar(heap));

  heap_destruir(heap, NULL);
  print_test("Se destruyó el heap", true);

  for(int i = 0; i < largo; i++) {
    free(valores[i]);
  }
}

void pruebas_heap_alumno(void) {
  pruebas_heap_vacio();
  pruebas_heap_encolar();
  pruebas_heap_encolar_int();
  pruebas_heap_desencolar();
  pruebas_heap_encolar_desencolar();
  pruebas_heap_encolar_con_destruir();
  pruebas_heap_volumen(500);
  prueba_heap_sort(10);

  int total_errores = failure_count();

  (total_errores > 0) ? printf(ANSI_COLOR_LGH_RED) : printf(ANSI_COLOR_LGH_GREEN);
  printf("Errores:");
  printf("%d\n", total_errores);
  printf(ANSI_COLOR_RESET);
}

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "abb.h"
#include "testing.h"

int comparar_int(const char* string1, const char* string2) {
  int numero1 = atoi(string1);
  int numero2 = atoi(string2);
  if(numero1 < numero2) return -1;
  if(numero1 == numero2) return 0;
  else return 1;
}

void pruebas_abb_vacio() {
  printf("\n---- INICIO DE PRUEBAS ABB VACÍO ----\n\n");

  abb_t* abb = abb_crear(strcmp, NULL);

  print_test("abb_borrar en abb recién creado es NULL", !abb_borrar(abb, "A"));
  print_test("abb_obtener en abb recién creado es NULL", !abb_obtener(abb, "A"));
  print_test("abb_pertenece en abb recién creado es false", !abb_pertenece(abb, "A"));
  print_test("Cantidad en abb recién creado es 0", abb_cantidad(abb) == 0);

  abb_destruir(abb);
}

void pruebas_iterar_abb_vacio() {
  printf("\n---- INICIO DE PRUEBAS ITERAR ABB VACÍO ----\n\n");

  abb_t* abb = abb_crear(strcmp, NULL);
  abb_iter_t* iter = abb_iter_in_crear(abb);

  print_test("Se pudo crear iterador en abb vacío", iter);
  print_test("Iterador está al final", abb_iter_in_al_final(iter));
  print_test("Avanzar iterador es false", !abb_iter_in_avanzar(iter));
  print_test("Ver actual de iterador es NULL", !abb_iter_in_ver_actual(iter));

  abb_iter_in_destruir(iter);
  abb_destruir(abb);
}

void pruebas_abb_guardar_NULL() {
  printf("\n--- INICIO PRUEBAS ABB GUARDAR NULL ----\n\n");

  abb_t* abb = abb_crear(strcmp, NULL);

  print_test("Cantidad es 0", abb_cantidad(abb) == 0);
  print_test("Se puede guardar NULL", abb_guardar(abb, "NULL", NULL));
  print_test("Cantidad es 1", abb_cantidad(abb) == 1);
  print_test("Pertenece con NULL devuelve true", abb_pertenece(abb, "NULL"));
  print_test("Obtener devuelve el dato: NULL", !abb_obtener(abb, "NULL"));
  print_test("Borrar devuelve el dato: NULL", !abb_borrar(abb, "NULL"));
  print_test("Cantidad es 0", abb_cantidad(abb) == 0);
  print_test("Pertenece con NULL devuelve false", !abb_pertenece(abb, "NULL"));
  print_test("Obtener devuelve NULL en abb vacío", !abb_obtener(abb, "NULL"));
  print_test("Borrar devuelve NULL en abb vacío", !abb_borrar(abb, "NULL"));

  abb_destruir(abb);
}

void pruebas_abb_insertar() {
  printf("\n---- INICIO PRUEBAS ABB INSERTAR ----\n\n");

  abb_t* abb = abb_crear(strcmp, NULL);

  char* alpha = "a";
  char* beta = "b";
  char* gamma = "g";

  print_test("Se pudo insertar: alpha", abb_guardar(abb, alpha, alpha));
  print_test("Cantidad es 1", abb_cantidad(abb) == 1);
  print_test("Pertenece devuelve true con: alpha", abb_pertenece(abb, alpha));
  print_test("Obtener devuelve el dato: alpha", strcmp(abb_obtener(abb, alpha), alpha) == 0);
  print_test("Se pudo insertar: gamma", abb_guardar(abb, gamma, gamma));
  print_test("Cantidad es 2", abb_cantidad(abb) == 2);
  print_test("Pertenece devuelve true con: gamma", abb_pertenece(abb, gamma));
  print_test("Obtener devuelve el dato: gamma", strcmp(abb_obtener(abb, gamma), gamma) == 0);
  print_test("Se pudo insertar: beta", abb_guardar(abb, beta, beta));
  print_test("Cantidad es 3", abb_cantidad(abb) == 3);
  print_test("Pertenece devuelve true con: beta", abb_pertenece(abb, beta));
  print_test("Obtener devuelve el dato: beta", strcmp(abb_obtener(abb, beta), beta) == 0);

  abb_destruir(abb);
}

void pruebas_abb_reemplazar() {
  printf("\n----INICIO PRUEBAS ABB REEMPLAZAR----\n\n");

  abb_t* abb = abb_crear(strcmp, NULL);

  char* alpha = "a",  *dato_alpha1 = "alpha1",  *dato_alpha2 = "alpha2";
  char* beta  = "b",  *dato_beta1  = "beta1",   *dato_beta2  = "beta2";
  char* gamma = "g",  *dato_gamma1 = "gamma",   *dato_gamma2 = "gamma2";

  print_test("Se insertó: alpha", abb_guardar(abb, alpha, dato_alpha1));
  print_test("Cantidad es 1", abb_cantidad(abb) == 1);
  print_test("Obtener devuelve el dato: dato_alpha1", abb_obtener(abb, alpha) == dato_alpha1);
  print_test("Se insertó: beta", abb_guardar(abb, beta, dato_beta1));
  print_test("Cantidad es 2", abb_cantidad(abb) == 2);
  print_test("Obtener devuelve el dato: dato_beta1", abb_obtener(abb, beta) == dato_beta1);
  print_test("Se insertó: gamma", abb_guardar(abb, gamma, dato_gamma1));
  print_test("Cantidad es 3", abb_cantidad(abb) == 3);
  print_test("Obtener devuelve el dato: dato_gamma1", abb_obtener(abb, gamma) == dato_gamma1);
  print_test("Se insertó con otro valor: alpha", abb_guardar(abb, alpha, dato_alpha2));
  print_test("Cantidad se mantiene: 3", abb_cantidad(abb) == 3);
  print_test("Obtener devuelve el dato: dato_alpha2", abb_obtener(abb, alpha) == dato_alpha2);
  print_test("Se insertó con otro valor: gamma", abb_guardar(abb, gamma, dato_gamma2));
  print_test("Cantidad se mantiene: 3", abb_cantidad(abb) == 3);
  print_test("Obtener devuelve el dato: dato_gamma2", abb_obtener(abb, gamma) == dato_gamma2);
  print_test("Se insertó con otro valor: beta", abb_guardar(abb, beta, dato_beta2));
  print_test("La cantidad se mantiene: 3", abb_cantidad(abb) == 3);
  print_test("Obtener devuelve el dato: dato_beta2", abb_obtener(abb, beta) == dato_beta2);

  abb_destruir(abb);
}

void pruebas_abb_reemplazar_con_destruir() {
  printf("\n---- INICIO PRUEBAS DE REEMPLAZAR CON DESTRUIR ----\n\n");

  abb_t* abb  = abb_crear(strcmp, free);

  char* alpha = "a";
  char* beta  = "b";

  char* dato_alpha1 = malloc(3*sizeof(char));
  char* dato_alpha2 = malloc(3*sizeof(char));
  char* dato_beta1  = malloc(3*sizeof(char));
  char* dato_beta2  = malloc(3*sizeof(char));

  print_test("Se insertó: alpha", abb_guardar(abb, alpha, dato_alpha1));
  print_test("Cantidad es 1", abb_cantidad(abb) == 1);
  print_test("Obtener devuelve el dato: dato_alpha1", abb_obtener(abb, alpha) == dato_alpha1);
  print_test("Se insertó: beta", abb_guardar(abb, beta, dato_beta1));
  print_test("Cantidad es 2", abb_cantidad(abb) == 2);
  print_test("Obtener devuelve el dato: dato_beta1", abb_obtener(abb, beta) == dato_beta1);
  print_test("Se insertó con otro valor: alpha", abb_guardar(abb, alpha, dato_alpha2));
  print_test("La cantidad se mantiene: 2", abb_cantidad(abb) == 2);
  print_test("Obtener devuelve el dato: dato_alpha2", abb_obtener(abb, alpha) == dato_alpha2);
  print_test("Se insertó con otro valor: beta", abb_guardar(abb, beta, dato_beta2));
  print_test("La cantidad se mantiene: 2", abb_cantidad(abb) == 2);
  print_test("Obtener devuelve el dato: dato_beta2", abb_obtener(abb, beta) == dato_beta2);

  abb_destruir(abb);
}

void pruebas_abb_borrar() {
  printf("\n---- INICIO DE PRUEBAS ABB BORRAR ----\n\n");

  abb_t* abb = abb_crear(strcmp, NULL);

  char* alpha = "a";
  char* beta  = "b";
  char* gamma = "g";
  char* epsilon = "e";

  print_test("Se insertó: alpha", abb_guardar(abb, alpha, alpha));
  print_test("Cantidad es 1", abb_cantidad(abb) == 1);
  print_test("Se insertó: beta", abb_guardar(abb, beta, beta));
  print_test("Cantidad es 2", abb_cantidad(abb) == 2);
  print_test("Se insertó: gamma", abb_guardar(abb, gamma, gamma));
  print_test("Cantidad es 3", abb_cantidad(abb) == 3);

  print_test("Pertenece es false: epsilon", !abb_pertenece(abb, epsilon));
  print_test("Obtener es NULL: epsilon", !abb_obtener(abb, epsilon));
  print_test("Borrar es NULL: epsilon", !abb_borrar(abb, epsilon));
  print_test("Pertenece es true: alpha", abb_pertenece(abb, alpha));
  print_test("Borrar devuelve el dato: alpha", abb_borrar(abb, alpha) == alpha);
  print_test("Cantidad es 2", abb_cantidad(abb) == 2);
  print_test("Pertenece es false: alpha", !abb_pertenece(abb, alpha));
  print_test("Obtener es NULL: alpha", !abb_obtener(abb, alpha));
  print_test("Borrar devuelve NULL con elemento ya borrado: alpha", !abb_borrar(abb, alpha));
  print_test("Se insertó: alpha", abb_guardar(abb, alpha, alpha));
  print_test("Cantidad es 3", abb_cantidad(abb) == 3);
  print_test("Pertenece es true: beta", abb_pertenece(abb, beta));
  print_test("Borrar devuelve el dato: beta", abb_borrar(abb, beta) == beta);
  print_test("Cantidad es 2", abb_cantidad(abb) == 2);
  print_test("Pertenece es false: beta", !abb_pertenece(abb, beta));
  print_test("Obtener es NULL: beta", !abb_obtener(abb, beta));
  print_test("Borrar devuelve NULL con elemento ya borrado: beta", !abb_borrar(abb, beta));
  print_test("Pertenece es true: gamma", abb_pertenece(abb, gamma));
  print_test("Borrar devuelve el dato: gamma", abb_borrar(abb, gamma) == gamma);
  print_test("Cantidad es 1", abb_cantidad(abb) == 1);
  print_test("Pertenece es false: gamma", !abb_pertenece(abb, gamma));
  print_test("Obtener es NULL: gamma", !abb_obtener(abb, gamma));
  print_test("Borrar devuelve NULL con elemento ya borrado: gamma", !abb_borrar(abb, gamma));
  print_test("Borrar devuelve el dato: alpha", abb_borrar(abb, alpha) == alpha);
  print_test("Cantidad es 0", abb_cantidad(abb) == 0);
  print_test("Pertenece es false: alpha", !abb_pertenece(abb, alpha));
  print_test("Obtener es NULL en abb vacío", !abb_obtener(abb, alpha));
  print_test("Borrar es NULL en abb vacío", !abb_borrar(abb, alpha));

  abb_destruir(abb);
}

void pruebas_abb_borrar_con_destruir() {
  printf("\n---- INICIO PRUEBAS ABB BORRAR CON DESTRUIR ----\n\n");

  abb_t* abb = abb_crear(strcmp, free);

  char* alpha = "a";
  char* beta  = "b";
  char* gamma = "g";

  char* dato_alpha = malloc(6*sizeof(char));
  char* dato_beta  = malloc(6*sizeof(char));
  char* dato_gamma = malloc(6*sizeof(char));

  print_test("Se insertó: alpha", abb_guardar(abb, alpha, dato_alpha));
  print_test("Cantidad es 1", abb_cantidad(abb) == 1);
  print_test("Se insertó: beta", abb_guardar(abb, beta, dato_beta));
  print_test("Cantidad es 2", abb_cantidad(abb) == 2);
  print_test("Se insertó: gamma", abb_guardar(abb, gamma, dato_gamma));
  print_test("Cantidad es 3", abb_cantidad(abb) == 3);
  print_test("Pertenece es true: alpha", abb_pertenece(abb, alpha));
  print_test("Borrar devuelve el dato: alpha", abb_borrar(abb, alpha) == dato_alpha);
  print_test("Cantidad es 2", abb_cantidad(abb) == 2);
  print_test("Pertenece es false: alpha", !abb_pertenece(abb, alpha));
  print_test("Obtener es NULL: alpha", !abb_obtener(abb, alpha));
  print_test("Borrar devuelve NULL con elemento ya borrado: alpha", !abb_borrar(abb, alpha));
  print_test("Se insertó: alpha", abb_guardar(abb, alpha, dato_alpha));
  print_test("Cantidad es 3", abb_cantidad(abb) == 3);
  print_test("Pertenece es true: beta", abb_pertenece(abb, beta));
  print_test("Borrar devuelve el dato: beta", abb_borrar(abb, beta) == dato_beta);
  print_test("Cantidad es 2", abb_cantidad(abb) == 2);
  print_test("Pertenece es false: beta", !abb_pertenece(abb, beta));
  print_test("Obtener es NULL: beta", !abb_obtener(abb, beta));
  print_test("Borrar devuelve NULL con elemento ya borrado: beta", !abb_borrar(abb, beta));
  print_test("Pertenece es true: gamma", abb_pertenece(abb, gamma));
  print_test("Borrar devuelve el dato: gamma", abb_borrar(abb, gamma) == dato_gamma);
  print_test("Cantidad es 1", abb_cantidad(abb) == 1);
  print_test("Pertenece es false: gamma", !abb_pertenece(abb, gamma));
  print_test("Obtener es NULL: gamma", !abb_obtener(abb, gamma));
  print_test("Borrar devuelve NULL con elemento ya borrado: gamma", !abb_borrar(abb, gamma));
  print_test("Borrar devuelve el dato: alpha", abb_borrar(abb, alpha) == dato_alpha);
  print_test("Cantidad es 0", abb_cantidad(abb) == 0);
  print_test("Pertenece es false: alpha", !abb_pertenece(abb, alpha));
  print_test("Obtener es NULL en abb vacío", !abb_obtener(abb, alpha));
  print_test("Borrar es NULL en abb vacío", !abb_borrar(abb, alpha));

  abb_destruir(abb);

  free(dato_alpha);
  free(dato_beta);
  free(dato_gamma);
}

void pruebas_abb_in_iter() {
  printf("\n---- INICIO PRUEBAS ABB ITERADOR EXTERNO INORDER ----\n\n");

  abb_t* abb = abb_crear(*comparar_int, NULL);

  print_test("Se pudo crear correctamente el abb", abb);

  int one = 1, two = 2, three = 3, four = 4, five = 5;

  const char* uno = "1";
  const char* dos = "2";
  const char* tres = "3";
  const char* cuatro = "4";
  const char* cinco = "5";

  print_test("Se insertó: tres", abb_guardar(abb, tres, &three));
  print_test("Cantidad es 1", abb_cantidad(abb) == 1);
  print_test("Se insertó: uno", abb_guardar(abb, uno, &one));
  print_test("Cantidad es 2", abb_cantidad(abb) == 2);
  print_test("Se insertó: dos", abb_guardar(abb, dos, &two));
  print_test("Cantidad es 3", abb_cantidad(abb) == 3);
  print_test("Se insertó: cuatro", abb_guardar(abb, cuatro, &four));
  print_test("Cantidad es 4", abb_cantidad(abb) == 4);
  print_test("Se insertó: cinco", abb_guardar(abb, cinco, &five));
  print_test("Cantidad es 5", abb_cantidad(abb) == 5);

  abb_iter_t* iter = abb_iter_in_crear(abb);

  print_test("Se creó el iterador en abb no vacío", iter);
  print_test("Iterador no está al final", !abb_iter_in_al_final(iter));
  print_test("Iterador apunta a: uno", strcmp(abb_iter_in_ver_actual(iter), uno)==0);
  print_test("Las claves no las mismas", abb_iter_in_ver_actual(iter) != uno);
  print_test("Se pudo avanzar", abb_iter_in_avanzar(iter));
  print_test("Iterador no está al final", !abb_iter_in_al_final(iter));
  print_test("Iterador apunta a: dos", strcmp(abb_iter_in_ver_actual(iter), dos)==0);
  print_test("Las claves no las mismas", abb_iter_in_ver_actual(iter) != dos);
  print_test("Se pudo avanzar", abb_iter_in_avanzar(iter));
  print_test("Iterador no está al final", !abb_iter_in_al_final(iter));
  print_test("Iterador apunta a: tres", strcmp(abb_iter_in_ver_actual(iter), tres)==0);
  print_test("Las claves no las mismas", abb_iter_in_ver_actual(iter) != tres);
  print_test("Se pudo avanzar", abb_iter_in_avanzar(iter));
  print_test("Iterador no está al final", !abb_iter_in_al_final(iter));
  print_test("Iterador apunta a: cuatro", strcmp(abb_iter_in_ver_actual(iter), cuatro)==0);
  print_test("Las claves no las mismas", abb_iter_in_ver_actual(iter) != cuatro);
  print_test("Se pudo avanzar", abb_iter_in_avanzar(iter));
  print_test("Iterador no está al final", !abb_iter_in_al_final(iter));
  print_test("Iterador apunta a: cinco", strcmp(abb_iter_in_ver_actual(iter), cinco)==0);
  print_test("Las claves no las mismas", abb_iter_in_ver_actual(iter) != cinco);
  print_test("Se pudo avanzar", abb_iter_in_avanzar(iter));
  print_test("Iterador está al final", abb_iter_in_al_final(iter));
  print_test("Ver actual al final devuelve NULL", !abb_iter_in_ver_actual(iter));
  print_test("No se puede avanzar al estar al final", !abb_iter_in_avanzar(iter));

  abb_iter_in_destruir(iter);
  print_test("Se destruyó el iterador", true);
  abb_destruir(abb);
  print_test("Se destruyó el abb", true);
}

void pruebas_abb_guardando_ints() {
  printf("\n---- INCIO PRUEBAS ABB GUARDAR INTS ----\n\n");

  abb_t* abb = abb_crear(*comparar_int, NULL);
  int one=1, two=2, three=3, four=4, five=5;

  const char* uno = "1";
  const char* dos = "2";
  const char* tres = "3";
  const char* cuatro = "4";
  const char* cinco = "5";

  print_test("abb_borrar en abb recién creado es NULL", !abb_borrar(abb, uno));
  print_test("abb_obtener en abb recién creado es NULL", !abb_obtener(abb, uno));
  print_test("abb_pertenece en abb recién creado es false", !abb_pertenece(abb, uno));
  print_test("Cantidad en abb recién creado es 0", abb_cantidad(abb) == 0);
  print_test("Inserto 1", abb_guardar(abb, uno, &one));
  print_test("Inserto 2", abb_guardar(abb, dos, &two));
  print_test("Inserto 4", abb_guardar(abb, cuatro, &four));
  print_test("Inserto 3", abb_guardar(abb, tres, &three));
  print_test("Inserto 5", abb_guardar(abb, cinco, &five));
  print_test("Borrar 1 devuelve valor 1", *((int*)abb_borrar(abb, uno)) == one);
  print_test("Borrar 2 devuelve valor 2", *((int*)abb_borrar(abb, dos)) == two);
  print_test("Borrar 4 devuelve valor 4", *((int*)abb_borrar(abb, cuatro)) == four);
  print_test("Borrar 3 devuelve valor 3", *((int*)abb_borrar(abb, tres)) == three);
  print_test("Borrar 5 devuelve valor 5", *((int*)abb_borrar(abb, cinco)) == five);
  abb_destruir(abb);
}

void pruebas_insertar_borrar_mismo_elem() {
  printf("\n---- INICIO PRUEBAS ABB INSERTAR Y BORRAR MISMO ELEMENTO ----\n\n");

  abb_t* abb = abb_crear(strcmp, free);

  char* uno = "alpha";
  char* one = malloc(sizeof(char));

  print_test("Inserto 1", abb_guardar(abb, uno, one));
  print_test("Borrar 1 devuelve valor1", (abb_borrar(abb, uno)) == one);
  print_test("Inserto 1", abb_guardar(abb, uno, one));
  print_test("Borrar 1 devuelve valor1", (abb_borrar(abb, uno)) == one);

  abb_destruir(abb);
  free(one);
}

bool buscar_string(const char* clave, void* a, void* b) {
  char* a_string = a;
  size_t* contador = b;
  if(strcmp(a_string,"Todo") == 0) return false;
  (*contador)++;
  return true;
}

void pruebas_abb_iter_interno_con_corte() {
  printf("\n---- INICIO PRUEBAS ABB ITERADOR INTERNO CON CORTE ----\n\n");

  abb_t* abb = abb_crear(*comparar_int,NULL);
  const char* uno = "1";
  const char* dos = "2";
  const char* tres = "3";
  const char* cuatro = "4";
  const char* cinco = "5";
  char* dato1 = "Hola";
  char* dato2 = "Como";
  char* dato3 = "Estas";
  char* dato4 = "Todo";
  char* dato5 = "Bien";

  print_test("Se insertó: tres", abb_guardar(abb, tres, dato3));
  print_test("Cantidad es 1", abb_cantidad(abb) == 1);
  print_test("Se insertó: uno", abb_guardar(abb, uno, dato1));
  print_test("Cantidad es 2", abb_cantidad(abb) == 2);
  print_test("Se insertó: dos", abb_guardar(abb, dos, dato2));
  print_test("Cantidad es 3", abb_cantidad(abb) == 3);
  print_test("Se insertó: cuatro", abb_guardar(abb, cuatro, dato4));
  print_test("Cantidad es 4", abb_cantidad(abb) == 4);
  print_test("Se insertó: cinco", abb_guardar(abb, cinco, dato5));
  print_test("Cantidad es 5", abb_cantidad(abb) == 5);

  size_t cantidad_iteraciones = 0;
  // buscar_string me busca "Todo" y guarda las iteraciones hasta
  // encontrarlo en cantidad_iteraciones.
  abb_in_order(abb, buscar_string, &cantidad_iteraciones);
  print_test("Se cortó el recorrido correctamente", cantidad_iteraciones == 3);
  abb_destruir(abb);
}

bool comprobar_in_order(const char* clave, void* dato, void* extra) {
  size_t* contador = extra;
  int* numero_dato = dato;
  (*contador)++;
  printf("Número de iteración: %i\n", *numero_dato);
  print_test("Se avanzó inorder", *contador == *numero_dato);
  return true;
}

void pruebas_abb_iter_interno() {
  printf("\n---- INICIO PRUEBAS ABB ITERADOR INTERNO SIN CORTE ----\n\n");

  abb_t* abb = abb_crear(strcmp, NULL);

  int dato1 = 1, dato2 = 2, dato3 = 3, dato4 = 4, dato5 = 5;
  const char* uno = "1";
  const char* dos = "2";
  const char* tres = "3";
  const char* cuatro = "4";
  const char* cinco = "5";

  print_test("Se insertó: tres", abb_guardar(abb, tres, &dato3));
  print_test("Cantidad es 1", abb_cantidad(abb) == 1);
  print_test("Se insertó: uno", abb_guardar(abb, uno, &dato1));
  print_test("Cantidad es 2", abb_cantidad(abb) == 2);
  print_test("Se insertó: dos", abb_guardar(abb, dos, &dato2));
  print_test("Cantidad es 3", abb_cantidad(abb) == 3);
  print_test("Se insertó: cuatro", abb_guardar(abb, cuatro, &dato4));
  print_test("Cantidad es 4", abb_cantidad(abb) == 4);
  print_test("Se insertó: cinco", abb_guardar(abb, cinco, &dato5));
  print_test("Cantidad es 5", abb_cantidad(abb) == 5);

  size_t contador = 0;
  abb_in_order(abb, comprobar_in_order, &contador);
  print_test("Se recorrió el árbol inorder", contador == 5);

  abb_destruir(abb);
}

void pruebas_abb_volumen(size_t largo) {
  printf("\n---- INICO PRUEBAS ABB VOLUMEN ----\n\n");

  abb_t* abb = abb_crear(strcmp, NULL);

  char (*claves)[10] = malloc(largo*10);
  unsigned* datos[largo];

  bool ok = true;
  for(unsigned i = 0; i < largo; i++) {
    datos[i] = malloc(sizeof(int));
    sprintf(claves[i], "%08d", i);
    *datos[i] = i;
    ok &= abb_guardar(abb, claves[i], datos[i]);
  }

  print_test("Insertar muchos elementos", ok);
  print_test("La cantidad es correcta", abb_cantidad(abb) == largo);

  for(size_t i = 0; i < largo; i++) {
    ok &= abb_pertenece(abb, claves[i]);
  }

  print_test("Pertenece muchos elementos", ok);

  for(size_t i = 0; i < largo; i++) {
    ok &= abb_obtener(abb, claves[i]) == datos[i];
  }

  print_test("Obtener muchos elementos", ok);

  for(size_t i = 0; i < largo; i++) {
    ok &= abb_borrar(abb, claves[i]) == datos[i];
  }

  print_test("Borrar muchos elementos", ok);
  print_test("Cantidad es 0", abb_cantidad(abb) == 0);

  abb_destruir(abb);

  abb = abb_crear(strcmp, free);

  for(size_t i = 0; i < largo; i++) {
    abb_guardar(abb, claves[i], datos[i]);
  }
  free(claves);

  abb_destruir(abb);
}

void pruebas_abb_iterar_volumen(size_t largo) {
  printf("\n---- INICIO PRUEBAS ABB ITERAR VOLUMEN ----\n\n");

  abb_t* abb = abb_crear(strcmp, NULL);

  char (*claves)[10] = malloc(largo*10);
  size_t datos[largo];

  bool ok = true;
  for(size_t i = 0; i < largo; i++) {
    sprintf(claves[i], "%zx", i);
    datos[i] = i;
    ok &= abb_guardar(abb, claves[i], &datos[i]);
  }

  abb_iter_t* iter = abb_iter_in_crear(abb);
  print_test("Iterador no está al final", !abb_iter_in_al_final(iter));

  ok = true;
  bool clave_diferente = true;
  size_t i = 0;
  while(i < largo && ok && clave_diferente) {
    ok &= !abb_iter_in_al_final(iter);
    ok &= (abb_iter_in_ver_actual(iter) != NULL);
    clave_diferente &= abb_iter_in_ver_actual(iter) != claves[i];
    ok &= abb_iter_in_avanzar(iter);
    i++;
  }

  print_test("Iteración en abb con muchos elementos", ok);
  print_test("Las claves no son iguales", clave_diferente);
  print_test("Recorrió todo el árbol", i == abb_cantidad(abb));
  print_test("Iterador está al final", abb_iter_in_al_final(iter));
  print_test("Ver actual devuelve NULL", !abb_iter_in_ver_actual(iter));
  print_test("Avanzar devuelve false", !abb_iter_in_avanzar(iter));

  free(claves);
  abb_iter_in_destruir(iter);
  abb_destruir(abb);
}

void pruebas_abb_in_iter_claves_catedra() {
  printf("\n---- INICIO PRUEBAS ABB ITERADOR EXTERNO INORDER CLAVES CATEDRA ----\n\n");

  abb_t* abb = abb_crear(*comparar_int, NULL);

  print_test("Se pudo crear correctamente el abb", abb);

  int one = 1, two = 2, three = 3;

  char *claves[] = {"2", "1", "3"};

  print_test("Prueba abb insertar clave1", abb_guardar(abb, claves[0], &two));
  print_test("Prueba abb insertar clave2", abb_guardar(abb, claves[1], &one));
  print_test("Prueba abb insertar clave3", abb_guardar(abb, claves[2], &three));
 
  abb_iter_t* iter = abb_iter_in_crear(abb);

  print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));
  print_test("Prueba abb iterador ver actual, es la primera", strcmp(abb_iter_in_ver_actual(iter), claves[1])==0);
  print_test("Prueba abb iterador ver actual, no es el mismo puntero", abb_iter_in_ver_actual(iter) != claves[1]);
  print_test("Prueba abb iterador avanzar es true", abb_iter_in_avanzar(iter));
  print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));
  print_test("Prueba abb iterador ver actual, es la del medio", strcmp(abb_iter_in_ver_actual(iter), claves[0])==0);
  print_test("Prueba abb iterador ver actual, no es el mismo puntero", abb_iter_in_ver_actual(iter) != claves[0]);
  print_test("Prueba abb iterador avanzar es true", abb_iter_in_avanzar(iter));
  print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));
  print_test("Prueba abb iterador ver actual, es la ultima", strcmp(abb_iter_in_ver_actual(iter), claves[2])==0);
  print_test("Prueba abb iterador ver actual, no es el mismo puntero", abb_iter_in_ver_actual(iter) != claves[2]);
  print_test("Prueba abb iterador avanzar es true", abb_iter_in_avanzar(iter));
  print_test("Prueba abb iterador esta al final, es true", abb_iter_in_al_final(iter));
  print_test("Prueba abb iterador ver actual, es NULL", !abb_iter_in_ver_actual(iter));
  print_test("Prueba abb iterador avanzar es false", !abb_iter_in_avanzar(iter));
  print_test("Prueba abb iterador esta al final, es true", abb_iter_in_al_final(iter));

  abb_iter_in_destruir(iter);
  print_test("Se destruyó el iterador", true);
  abb_destruir(abb);
  print_test("Se destruyó el abb", true);
}

void pruebas_abb_alumno() {
  pruebas_abb_vacio();
  pruebas_abb_guardar_NULL();
  pruebas_abb_insertar();
  pruebas_abb_guardando_ints();
  pruebas_abb_reemplazar();
  pruebas_abb_reemplazar_con_destruir();
  pruebas_abb_borrar();
  pruebas_abb_borrar_con_destruir();
  pruebas_insertar_borrar_mismo_elem();
  pruebas_iterar_abb_vacio();
  pruebas_abb_in_iter();
  pruebas_abb_iter_interno_con_corte();
  pruebas_abb_iter_interno();
  pruebas_abb_in_iter_claves_catedra();
  pruebas_abb_volumen(500);
  pruebas_abb_iterar_volumen(500);
}

#include "lista.h"
#include "cola.h"
#include "pila.h"
#include "vector_dinamico.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>

void prueba_lista_vacia() {
    printf("----PRUEBA INSERTAR ULTIMO ----\n\n");
    lista_t *l = lista_crear();
    print_test("La lista fue creada", l != NULL);
    print_test("La lista esta vacia", lista_esta_vacia(l) == true);
    print_test("El largo de la lista es 0", lista_largo(l) == 0);
    print_test("Ver primero en lista devuelve NULL", lista_ver_primero(l) == NULL);
    print_test("Ver ultimo en lista devuelve NULL", lista_ver_ultimo(l) == NULL);
    print_test("Borrar primero devuelve NULL",lista_borrar_primero(l) == NULL);
    lista_destruir(l,NULL);
}

void prueba_insertar_primero() {
	printf("----PRUEBA INSERTAR PRIMERO ----\n\n");
	lista_t *l = lista_crear();
	int a=5;
    print_test("La lista fue creada", l != NULL);
    print_test("La lista esta vacia", lista_esta_vacia(l) == true);
    print_test("El largo de la lista es 0", lista_largo(l) == 0);
    print_test("Ver primero en lista devuelve NULL", lista_ver_primero(l) == NULL);
    print_test("La lista fue insertada al principio con valor 5", lista_insertar_primero(l,&a) == true);
    print_test("El largo de la lista es 1", lista_largo(l) == 1);
    print_test("La lista no esta vacia", !lista_esta_vacia(l) == true);
    print_test("Ver primero en lista devuelve 5", lista_ver_primero(l) == &a);
    print_test("Ver ultimo en lista devuelve 5", lista_ver_ultimo(l) == &a);
    lista_destruir(l,NULL);
    print_test("Los valores enlistados no fueron modificados", a==5);
}

void prueba_insertar_primero_volumen() {
    printf("----PRUEBA INSERTANDO PRIMERO GRAN CANTIDAD ----\n\n");
    lista_t *l = lista_crear();
    int tam=5;
    int vector[tam];
    for (int i=0;i<tam;i++) { //Lleno el vector
        vector[i]=tam-i;
    }

    print_test("La lista fue creada", l != NULL);
    print_test("La lista esta vacia", lista_esta_vacia(l) == true);
    print_test("El largo de la lista es 0", lista_largo(l) == 0);
    print_test("Ver primero en lista devuelve NULL", lista_ver_primero(l) == NULL);
    for (int i=0;i<tam;i++) {
        printf("Insertare el numero: %d\n",vector[i]);
        print_test("La lista fue insertada al principio con el numero", lista_insertar_primero(l,&vector[i]) == true);
    }
    print_test("El largo de la lista es tam", lista_largo(l) == tam);
    for (int i=tam-1;i>=0;i--) {
        print_test("Borro el primero, devuelve numero", *(int*)lista_borrar_primero(l) == vector[i]);
        printf("El valor numerico es %d\n",vector[i]);
    }
    print_test("El largo de la lista es 0", lista_largo(l) == 0);
    print_test("Ver primero en lista devuelve NULL", lista_ver_primero(l) == NULL);
    print_test("La lista esta vacia", lista_esta_vacia(l) == true);
    lista_destruir(l,NULL);
}

void prueba_insertar_ultimo() {
	printf("----PRUEBA INSERTAR ULTIMO ----\n\n");
	lista_t *l = lista_crear();
    int a=5;
    print_test("La lista fue creada", l != NULL);
    print_test("La lista esta vacia", lista_esta_vacia(l) == true);
    print_test("El largo de la lista es 0", lista_largo(l) == 0);
    print_test("Ver primero en lista devuelve NULL", lista_ver_primero(l) == NULL);
    print_test("La lista fue insertada al final con valor 5", lista_insertar_ultimo(l,&a) == true);
    print_test("El largo de la lista es 1", lista_largo(l) == 1);
    print_test("La lista no esta vacia", !lista_esta_vacia(l) == true);
    print_test("Ver primero en lista devuelve 5", lista_ver_primero(l) == &a);
    print_test("Ver ultimo en lista devuelve 5", lista_ver_ultimo(l) == &a);
    print_test("Los valores enlistados no fueron modificados", a==5);
    lista_destruir(l,NULL);
}

void prueba_insertar_ultimo_volumen() {
    printf("----PRUEBA INSERTANDO ULTIMO GRAN CANTIDAD ----\n\n");
    lista_t *l = lista_crear();
    int tam=5;
    int vector[tam];
    for (int i=0;i<tam;i++) { //Lleno el vector
        vector[i]=i;
    }
    for (int i=0;i<tam;i++) {
        printf("Insertare el numero: %d\n",vector[i]);
        print_test("La lista fue insertada al final con el numero", lista_insertar_ultimo(l,&vector[i]) == true);
    }
    print_test("El largo de la lista es tam", lista_largo(l) == tam);
    for (int i=0;i<tam;i++) {
        print_test("Borro el primero, devuelve numero", *(int*)lista_borrar_primero(l) == vector[i]);
        printf("El valor numerico es %d\n",vector[i]);
    }
    print_test("El largo de la lista es 0", lista_largo(l) == 0);
    print_test("Ver primero en lista devuelve NULL", lista_ver_primero(l) == NULL);
    print_test("La lista esta vacia", lista_esta_vacia(l) == true);
    lista_destruir(l,NULL);
}

void pila_destruir_wrapper(void* elem) {
    pila_destruir((pila_t*) elem);
}

void prueba_insertar_ult_pri_pilas() {
    printf("----PRUEBA INSERTANDO ULTIMO Y PRIMERO PILAS ----\n\n");
    pila_t *p1 = pila_crear();
    pila_t *p2 = pila_crear();
    char valor1='c';
    int valor2=22;
    int valor3[]={2,1,4,0};
    void* valor4=NULL;
    print_test("La pila 1 fue creada", p1 != NULL);
    print_test("La pila está vacía", pila_esta_vacia(p1));
    print_test("Apile en pila valor1, devuelve true",pila_apilar(p1,&valor1) == true);
    print_test("Apile en pila valor2, devuelve true",pila_apilar(p1,&valor2) == true);
    print_test("Apile en pila valor3, devuelve true",pila_apilar(p1,&valor3) == true);
    print_test("Apile en pila valor4, devuelve true",pila_apilar(p1,valor4) == true);

    print_test("La pila 2 fue creada", p2 != NULL);
    print_test("La pila 2 está vacía", pila_esta_vacia(p2));
    print_test("Apile en pila valor1, devuelve true",pila_apilar(p2,&valor1) == true);
    print_test("Apile en pila valor2, devuelve true",pila_apilar(p2,&valor2) == true);
    print_test("Apile en pila valor3, devuelve true",pila_apilar(p2,&valor3) == true);
    print_test("Apile en pila valor4, devuelve true",pila_apilar(p2,valor4) == true);

    lista_t *l = lista_crear();
    print_test("La lista fue creada", l != NULL);
    print_test("La lista esta vacia", lista_esta_vacia(l) == true);
    print_test("El largo de la lista es 0", lista_largo(l) == 0);
    print_test("Ver primero en lista devuelve NULL", lista_ver_primero(l) == NULL);

    print_test("La lista fue insertada al principio con pila 1", lista_insertar_primero(l,p1) == true);
    print_test("La lista fue insertada al final con pila 2", lista_insertar_ultimo(l,p2) == true);
    print_test("Borro el primero, devuelve pila 1", lista_borrar_primero(l) == p1);
    pila_destruir(p1);
    print_test("Borro el primero, devuelve pila 2", lista_borrar_primero(l) == p2);
    pila_destruir(p2);
    print_test("El largo de la lista es 0", lista_largo(l) == 0);
    print_test("Ver primero en lista devuelve NULL", lista_ver_primero(l) == NULL);
    print_test("La lista esta vacia", lista_esta_vacia(l) == true);
    lista_destruir(l,NULL);
}

void prueba_insertar_ult_pri_pilas_w() {
    printf("----PRUEBA INSERTANDO ULTIMO Y PRIMERO PILAS (WRAPPER) ----\n\n");
    pila_t *p1= pila_crear();
    pila_t *p2= pila_crear();
    char valor1='c';
    int valor2=22;
    int valor3[]={2,1,4,0};
    void* valor4=NULL;
    print_test("La pila 1 fue creada", p1 != NULL);
    print_test("La pila 1 está vacía", pila_esta_vacia(p1));
    print_test("Apile en pila valor1, devuelve true",pila_apilar(p1,&valor1) == true);
    print_test("Apile en pila valor2, devuelve true",pila_apilar(p1,&valor2) == true);
    print_test("Apile en pila valor3, devuelve true",pila_apilar(p1,&valor3) == true);
    print_test("Apile en pila valor4, devuelve true",pila_apilar(p1,valor4) == true);

    print_test("La pila 2 fue creada", p2 != NULL);
    print_test("La pila 2 está vacía", pila_esta_vacia(p2));
    print_test("Apile en pila valor1, devuelve true",pila_apilar(p2,&valor1) == true);
    print_test("Apile en pila valor2, devuelve true",pila_apilar(p2,&valor2) == true);
    print_test("Apile en pila valor3, devuelve true",pila_apilar(p2,&valor3) == true);
    print_test("Apile en pila valor4, devuelve true",pila_apilar(p2,valor4) == true);

    lista_t *l = lista_crear();
    print_test("La lista fue creada", l != NULL);
    print_test("La lista esta vacia", lista_esta_vacia(l) == true);
    print_test("El largo de la lista es 0", lista_largo(l) == 0);
    print_test("Ver primero en lista devuelve NULL", lista_ver_primero(l) == NULL);
    print_test("La lista fue insertada al principio con pila 1", lista_insertar_primero(l,p1) == true);
    print_test("La lista fue insertada al final con pila 2", lista_insertar_ultimo(l,p2) == true);
    print_test("El largo de la lista es 2", lista_largo(l) == 2);
    lista_destruir(l,&pila_destruir_wrapper);
    print_test("Los valores enlistados no fueron modificados", valor1=='c' && valor2==22 && valor4==NULL);
}
void prueba_iterador_ext_vacia() {
    printf("----PRUEBA ITERADOR----\n\n");
    lista_t *l = lista_crear();
    lista_iter_t* iter=lista_iter_crear(l);
    print_test("La lista fue creada", l != NULL);
    print_test("EL iterador fue creado", iter != NULL);
    print_test("La lista esta vacia", lista_esta_vacia(l) == true);
    print_test("El largo de la lista es 0", lista_largo(l) == 0);
    print_test("Iterador al final en lista recien creada devuelve true", lista_iter_al_final(iter) == true);
    print_test("Avanzar en lista vacia(iterador al final) devuelve false", lista_iter_avanzar(iter) == false);
    print_test("Ver actual en lista vacia(iterador al final) devuelve NULL", lista_iter_ver_actual(iter) == NULL);
    print_test("Borrar en lista vacia(iterador al final) devuelve NULL", lista_iter_borrar(iter) == NULL);
    lista_iter_destruir(iter);
    lista_destruir(l,NULL);   
}

void vector_destruir_wrapper(void* elem) {
    vector_destruir((vector_t*) elem);
}

void prueba_iterador_1_vd() {
    printf("----PRUEBA ITERADOR 1 VD----\n\n");
    lista_t *l = lista_crear();
    lista_iter_t* iter=lista_iter_crear(l);
    vector_t* vec1=vector_crear(2);
    vector_guardar(vec1, 0, 5);
    vector_guardar(vec1, 1, 3);;

    print_test("La lista fue creada", l != NULL);
    print_test("EL iterador fue creado", iter != NULL);
    print_test("La lista esta vacia", lista_esta_vacia(l) == true);
    print_test("El largo de la lista es 0", lista_largo(l) == 0);
    print_test("Iterador al final en lista recien creada devuelve true", lista_iter_al_final(iter) == true);
    print_test("Avanzar en lista vacia(iterador al final) devuelve false", lista_iter_avanzar(iter) == false);
    print_test("Ver actual en lista vacia(iterador al final) devuelve NULL", lista_iter_ver_actual(iter) == NULL);
    print_test("Inserto con iterador en lista recien creada, devuelve true", lista_iter_insertar(iter,vec1) == true);
    print_test("Ver actual devuelve 5", lista_iter_ver_actual(iter) == vec1);
    print_test("Ver primero en lista devuelve 5", lista_ver_primero(l) == vec1);
    print_test("Ver ultimo en lista devuelve 5", lista_ver_ultimo(l) == vec1);
    print_test("El largo de la lista es 1", lista_largo(l) == 1);
    lista_iter_destruir(iter);
    lista_destruir(l,&vector_destruir_wrapper);
}

void prueba_iter_insertar_borde() {
    printf("----PRUEBA ITERADOR INSERTAR CAMBIOS BORDE----\n\n");
    lista_t *l = lista_crear();
    lista_iter_t* iter=lista_iter_crear(l);

    int a=5,b=53,d=42,e=105,f=82;
    char c='c';
    
    print_test("La lista fue creada", l != NULL);
    print_test("EL iterador fue creado", iter != NULL);
    print_test("La lista esta vacia", lista_esta_vacia(l) == true);
    print_test("El largo de la lista es 0", lista_largo(l) == 0);
    print_test("Iterador al final en lista recien creada devuelve true", lista_iter_al_final(iter) == true);
    print_test("Avanzar en lista vacia(iterador al final) devuelve false", lista_iter_avanzar(iter) == false);
    print_test("Ver actual en lista vacia(iterador al final) devuelve NULL", lista_iter_ver_actual(iter) == NULL);
    print_test("Inserto con iterador valor 5, en lista recien creada, devuelve true", lista_iter_insertar(iter,&a) == true);
    print_test("Ver ultimo en lista devuelve 5", lista_ver_ultimo(l) == &a);
    print_test("Ver primero en lista devuelve 5", lista_ver_primero(l) == &a); 
    print_test("Inserto con iterador valor 53, devuelve true", lista_iter_insertar(iter,&b) == true);
    print_test("Ver ultimo en lista devuelve 5", lista_ver_ultimo(l) == &a);
    print_test("Ver primero en lista devuelve 53", lista_ver_primero(l) == &b); 
    print_test("Ver actual devuelve 53", lista_iter_ver_actual(iter) == &b);
    print_test("El largo de la lista es 2", lista_largo(l) == 2);
    print_test("Inserto con iterador valor c, devuelve true", lista_iter_insertar(iter,&c) == true);
    print_test("Ver actual devuelve c", lista_iter_ver_actual(iter) == &c);
    print_test("Ver ultimo en lista devuelve 5", lista_ver_ultimo(l) == &a);
    print_test("Ver primero en lista devuelve c", lista_ver_primero(l) == &c);
    print_test("El largo de la lista es 3", lista_largo(l) == 3);
    print_test("Avanzar en lista devuelve true", lista_iter_avanzar(iter) == true);
    print_test("Inserto con iterador valor 42, devuelve true", lista_iter_insertar(iter,&d) == true);
    print_test("Ver actual devuelve 42", lista_iter_ver_actual(iter) == &d);
    print_test("Ver ultimo en lista devuelve 5", lista_ver_ultimo(l) == &a);
    print_test("Ver primero en lista devuelve c", lista_ver_primero(l) == &c);
    print_test("El largo de la lista es 4", lista_largo(l) == 4);
    print_test("Avanzar en lista devuelve true", lista_iter_avanzar(iter) == true);
    print_test("Ver actual devuelve 53", lista_iter_ver_actual(iter) == &b);
    print_test("Avanzar en lista devuelve true", lista_iter_avanzar(iter) == true);
    print_test("Ver actual devuelve 5", lista_iter_ver_actual(iter) == &a);
    print_test("Inserto con iterador valor 105, devuelve true", lista_iter_insertar(iter,&e) == true);
    print_test("El largo de la lista es 5", lista_largo(l) == 5);
    print_test("Ver ultimo en lista devuelve 5", lista_ver_ultimo(l) == &a);
    print_test("Avanzar en lista devuelve true", lista_iter_avanzar(iter) == true);
    print_test("Ver actual devuelve 5", lista_iter_ver_actual(iter) == &a);
    print_test("Avanzar en lista devuelve true", lista_iter_avanzar(iter) == true);
    print_test("Ver actual en lista (iterador al final) devuelve NULL", lista_iter_ver_actual(iter) == NULL);
    print_test("Avanzar en lista (iterador al final) devuelve false", lista_iter_avanzar(iter) == false);
    print_test("Inserto con iterador valor f, devuelve true", lista_iter_insertar(iter,&f) == true);
    print_test("Ver ultimo en lista devuelve f", lista_ver_ultimo(l) == &f);
    print_test("Ver primero en lista devuelve c", lista_ver_primero(l) == &c);
    print_test("Avanzar en lista devuelve true", lista_iter_avanzar(iter) == true);
    print_test("Avanzar en lista (iterador al final) devuelve false", lista_iter_avanzar(iter) == false);
    print_test("Ver actual en lista (iterador al final) devuelve NULL", lista_iter_ver_actual(iter) == NULL);
    lista_iter_destruir(iter);
    lista_destruir(l,NULL);
}

void prueba_iter_borrar_borde() {
    printf("----PRUEBA ITERADOR BORRAR CAMBIOS BORDE----\n\n");
    lista_t *l = lista_crear();
    lista_iter_t* iter=lista_iter_crear(l);

    int a=5,b=4,c=3,d=2,e=1;
    
    print_test("La lista fue creada", l != NULL);
    print_test("EL iterador fue creado", iter != NULL);
    print_test("La lista esta vacia", lista_esta_vacia(l) == true);
    print_test("El largo de la lista es 0", lista_largo(l) == 0);
    print_test("Iterador al final en lista recien creada devuelve true", lista_iter_al_final(iter) == true);
    print_test("Avanzar en lista vacia(iterador al final) devuelve false", lista_iter_avanzar(iter) == false);
    print_test("Ver actual en lista vacia(iterador al final) devuelve NULL", lista_iter_ver_actual(iter) == NULL);
    print_test("Inserto con iterador valor 5, en lista recien creada, devuelve true", lista_iter_insertar(iter,&a) == true);
    print_test("Inserto con iterador valor 4, devuelve true", lista_iter_insertar(iter,&b) == true);
    print_test("Inserto con iterador valor 3, devuelve true", lista_iter_insertar(iter,&c) == true);
    print_test("Inserto con iterador valor 2, devuelve true", lista_iter_insertar(iter,&d) == true);
    print_test("Inserto con iterador valor 1, devuelve true", lista_iter_insertar(iter,&e) == true);
    print_test("Ver ultimo en lista devuelve 5", lista_ver_ultimo(l) == &a);
    print_test("Ver primero en lista devuelve 1", lista_ver_primero(l) == &e);
    print_test("El largo de la lista es 5", lista_largo(l) == 5);
    print_test("Borro con iterador al principio devuelve 1", lista_iter_borrar(iter) == &e);
    print_test("El largo de la lista es 4", lista_largo(l) == 4);
    print_test("Ver primero en lista devuelve 2", lista_ver_primero(l) == &d);
    print_test("Ver ultimo en lista devuelve 5", lista_ver_ultimo(l) == &a);
    print_test("Avanzar en lista devuelve true", lista_iter_avanzar(iter) == true);
    print_test("Borro con iterador devuelve 3", lista_iter_borrar(iter) == &c);
    print_test("El largo de la lista es 3", lista_largo(l) == 3);
    print_test("Ver primero en lista devuelve 2", lista_ver_primero(l) == &d);
    print_test("Ver ultimo en lista devuelve 5", lista_ver_ultimo(l) == &a);
    print_test("Ver actual devuelve 4", lista_iter_ver_actual(iter) == &b);
    print_test("Avanzar en lista devuelve true", lista_iter_avanzar(iter) == true);
    print_test("Ver actual devuelve 5", lista_iter_ver_actual(iter) == &a);
    print_test("Borro con iterador devuelve 5", lista_iter_borrar(iter) == &a);
    print_test("El largo de la lista es 2", lista_largo(l) == 2);
    print_test("Ver primero en lista devuelve 2", lista_ver_primero(l) == &d);
    print_test("Ver ultimo en lista devuelve 4", lista_ver_ultimo(l) == &b);
    print_test("Borro con iterador al final, devuelve NULL", lista_iter_borrar(iter) == NULL);
    print_test("Avanzar en lista (iterador al final) devuelve false", lista_iter_avanzar(iter) == false);
    print_test("Ver actual en lista (iterador al final) devuelve NULL", lista_iter_ver_actual(iter) == NULL);
    print_test("El largo de la lista es 2", lista_largo(l) == 2);
    lista_iter_destruir(iter);
    lista_destruir(l,NULL);
}

bool sumar(void* a, void*b) {
    int* a_int=a;
    int* b_int=b;
    *b_int+=*a_int;
    return true;
}

bool imprimir_pares(void*a, void*b) {
    int* a_int=a;
    int* contador=b;
    if (*a_int%2==0) {
        printf("El numero: %d es par\n",*a_int);
        (*contador)++;
    }
    return true;
}

bool buscar_numero_3(void*a, void* b) {
    int* a_int=a;
    int* posicion=b;
    if (*a_int == 3) { //Corto una vez que lo encontre
        printf("Lo encontre! el numero a encontrar era el: %d\n",*a_int);
        printf("Y estaba en la posicion: %d\n",*posicion);
        return false;
    }
    (*posicion)++;
    return true;
}

void prueba_iter_interno() {
    printf("----PRUEBA ITERADOR INTERNO SIN CORTE----\n\n");
    lista_t *l = lista_crear();
    lista_iter_t* iter=lista_iter_crear(l);
    int suma=0;
    int contador_pares=0;
    int a=5,b=4,c=3,d=2,e=1;
    
    print_test("La lista fue creada", l != NULL);
    print_test("EL iterador fue creado", iter != NULL);
    print_test("La lista esta vacia", lista_esta_vacia(l) == true);
    print_test("El largo de la lista es 0", lista_largo(l) == 0);
    print_test("Iterador al final en lista recien creada devuelve true", lista_iter_al_final(iter) == true);
    print_test("Avanzar en lista vacia(iterador al final) devuelve false", lista_iter_avanzar(iter) == false);
    print_test("Ver actual en lista vacia(iterador al final) devuelve NULL", lista_iter_ver_actual(iter) == NULL);
    print_test("Inserto con iterador valor 5, en lista recien creada, devuelve true", lista_iter_insertar(iter,&a) == true);
    print_test("Inserto con iterador valor 4, devuelve true", lista_iter_insertar(iter,&b) == true);
    print_test("Inserto con iterador valor 3, devuelve true", lista_iter_insertar(iter,&c) == true);
    print_test("Inserto con iterador valor 2, devuelve true", lista_iter_insertar(iter,&d) == true);
    print_test("Inserto con iterador valor 1, devuelve true", lista_iter_insertar(iter,&e) == true);
    print_test("Ver ultimo en lista devuelve 5", lista_ver_ultimo(l) == &a);
    print_test("Ver primero en lista devuelve 1", lista_ver_primero(l) == &e);
    lista_iterar(l,sumar,&suma);
    print_test("Ver suma es 15",suma == 15);
    lista_iterar(l,imprimir_pares,&contador_pares);
    print_test("Contador de pares es 2",contador_pares == 2);
    lista_iter_destruir(iter);
    lista_destruir(l,NULL);
}

void prueba_iter_interno_null() {
    printf("----PRUEBA ITERADOR INTERNO FUNCION NULL----\n\n");
    lista_t *l = lista_crear();
    lista_iter_t* iter=lista_iter_crear(l);
    print_test("La lista fue creada", l != NULL);
    print_test("EL iterador fue creado", iter != NULL);
    lista_iterar(l,NULL,NULL);
    lista_iter_destruir(iter);
    lista_destruir(l,NULL);
}

void prueba_iter_iterno_corte() {
    printf("----PRUEBA ITERADOR INTERNO CON CORTE----\n\n");
    lista_t *l = lista_crear();
    lista_iter_t* iter=lista_iter_crear(l);
    int posicion=0;
    int a=5,b=4,c=3,d=2,e=1;
    
    print_test("La lista fue creada", l != NULL);
    print_test("EL iterador fue creado", iter != NULL);
    print_test("La lista esta vacia", lista_esta_vacia(l) == true);
    print_test("El largo de la lista es 0", lista_largo(l) == 0);
    print_test("Iterador al final en lista recien creada devuelve true", lista_iter_al_final(iter) == true);
    print_test("Avanzar en lista vacia(iterador al final) devuelve false", lista_iter_avanzar(iter) == false);
    print_test("Ver actual en lista vacia(iterador al final) devuelve NULL", lista_iter_ver_actual(iter) == NULL);
    print_test("Inserto con iterador valor 5, en lista recien creada, devuelve true", lista_iter_insertar(iter,&a) == true);
    print_test("Inserto con iterador valor 4, devuelve true", lista_iter_insertar(iter,&b) == true);
    print_test("Inserto con iterador valor 3, devuelve true", lista_iter_insertar(iter,&c) == true);
    print_test("Inserto con iterador valor 2, devuelve true", lista_iter_insertar(iter,&d) == true);
    print_test("Inserto con iterador valor 1, devuelve true", lista_iter_insertar(iter,&e) == true);
    print_test("Ver ultimo en lista devuelve 5", lista_ver_ultimo(l) == &a);
    print_test("Ver primero en lista devuelve 1", lista_ver_primero(l) == &e);
    lista_iterar(l,buscar_numero_3,&posicion);
    lista_iter_destruir(iter);
    lista_destruir(l,NULL);
}

void pruebas_lista_alumno(){
    //Pruebas Lista
    prueba_lista_vacia();
	prueba_insertar_primero();
    prueba_insertar_primero_volumen();
	prueba_insertar_ultimo();
    prueba_insertar_ultimo_volumen();
    prueba_insertar_ult_pri_pilas();
    prueba_insertar_ult_pri_pilas_w();
    //Pruebas Iterador Externo
    prueba_iterador_ext_vacia();
    prueba_iterador_1_vd();
    prueba_iter_insertar_borde();
    prueba_iter_borrar_borde();
    //Pruebas Iterador Interno
    prueba_iter_interno();
    prueba_iter_interno_null();
    prueba_iter_iterno_corte();
    //Se podrian agregar pruebas como creo una lista que tiene colas
    // y la inserto en otra lista nueva, etc, o parecidas a las de la cola.
    //O condiciones de corte de iteradores con pilas etc.
}


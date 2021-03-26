#include "cola.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include "vector_dinamico.h"
#include "pila.h"

void prueba_cola_vacia() {
    printf("----PRUEBA CON COLA VACIA----\n\n");
    cola_t *c = cola_crear();
    print_test("La cola fue creada", c != NULL);
    print_test("La cola esta vacia", cola_esta_vacia(c) == true);
    print_test("Ver primero en cola devuelve NULL", cola_ver_primero(c) == NULL);
    print_test("Desencolo cola vacia, devuelve NULL", cola_desencolar(c) == NULL);
    print_test("Ver primero en cola devuelve NULL", cola_ver_primero(c) == NULL);
    cola_destruir(c,NULL);
}

void prueba_encolando_1_elemento() {
    printf("----PRUEBA ENCOLANDO 1 ELEMENTO ----\n\n");
    cola_t *c = cola_crear();
    int a=5;
    print_test("La cola fue creada", c != NULL);
    print_test("La cola esta vacia", cola_esta_vacia(c) == true);
    print_test("Ver primero en cola devuelve NULL", cola_ver_primero(c) == NULL);
    print_test("La cola fue encolada con valor 5", cola_encolar(c,&a) == true);
    print_test("La cola no esta vacia", !cola_esta_vacia(c) == true);
    print_test("Desencolo el primero, devuelve 5", cola_desencolar(c) == &a);
    print_test("Ver primero en cola devuelve NULL", cola_ver_primero(c) == NULL);
    print_test("La cola esta vacia", cola_esta_vacia(c) == true);
    cola_destruir(c,NULL);
    print_test("Los valores encolados no fueron modificados", a==5);
}

void prueba_encolando_null() {
	printf("----PRUEBA ENCOLANDO NULL'S ----\n\n");
	cola_t *c = cola_crear();
	int a=5;
    void* b=NULL;
	int f=53;
    void* d=NULL;
    print_test("La cola fue creada", c != NULL);
    print_test("La cola esta vacia", cola_esta_vacia(c) == true);
    print_test("Ver primero en cola devuelve NULL", cola_ver_primero(c) == NULL);
    print_test("La cola fue encolada con valor 5", cola_encolar(c,&a) == true);
    print_test("La cola no esta vacia", !cola_esta_vacia(c) == true);
    print_test("Ver primero en cola devuelve 5", cola_ver_primero(c) == &a);
    print_test("La cola fue encolada con valor NULL", cola_encolar(c,b) == true);
    print_test("Ver primero en cola devuelve 5", cola_ver_primero(c) == &a);
    print_test("Desencolo el primero, devuelve 5", cola_desencolar(c) == &a);
    print_test("Ver primero en cola devuelve valor NULL", cola_ver_primero(c) == b);
    print_test("La cola fue encolada con valor 53", cola_encolar(c,&f) == true);
    print_test("La cola fue encolada con valor NULL", cola_encolar(c,d) == true);
    print_test("Desencolo el primero, devuelve valor NULL", cola_desencolar(c) == b);
    print_test("Desencolo el primero, devuelve 53", cola_desencolar(c) == &f);
    print_test("Desencolo el primero, devuelve valor NULL", cola_desencolar(c) == d);
    print_test("Ver primero en cola devuelve NULL", cola_ver_primero(c) == NULL);
    print_test("La cola esta vacia", cola_esta_vacia(c) == true);
    cola_destruir(c,NULL);
    print_test("Los valores encolados no fueron modificados", a==5 && b==NULL && f==53 && d==NULL);
}

void prueba_varios_tipos() {
	printf("----PRUEBAS VARIOS TIPOS ENCOLADOS ----\n\n");
	cola_t *c = cola_crear();
	int a=5;
	int b=53;
	char p='s';
	int vector[]={2,3,0};
    print_test("La cola fue creada", c != NULL);
    print_test("La cola esta vacia", cola_esta_vacia(c) == true);
    print_test("Ver primero en cola devuelve NULL", cola_ver_primero(c) == NULL);
    print_test("La cola fue encolada con valor 5", cola_encolar(c,&a) == true);
    print_test("La cola no esta vacia", !cola_esta_vacia(c) == true);
    print_test("Ver primero en cola devuelve 5", cola_ver_primero(c) == &a);
    print_test("La cola fue encolada con valor 53", cola_encolar(c,&b) == true);
    print_test("La cola fue encolada con valor p", cola_encolar(c,&p) == true);
    print_test("La cola fue encolada con valor vector", cola_encolar(c,vector) == true);
    print_test("Desencolo el primero, devuelve 5", cola_desencolar(c) == &a);
    print_test("Desencolo el primero, devuelve 53", cola_desencolar(c) == &b);
    print_test("Desencolo el primero, devuelve p", cola_desencolar(c) == &p);
    print_test("Ver primero en cola devuelve vector", cola_ver_primero(c) == vector);
    print_test("Desencolo el primero, devuelve vector", cola_desencolar(c) == vector);
    print_test("La cola esta vacia", cola_esta_vacia(c) == true);                       
    cola_destruir(c,NULL);                                                              
}

void vector_destruir_wrapper(void* elem) {
	vector_destruir((vector_t*) elem);
}

void prueba_vector_dinamico_encolado() {
    printf("----PRUEBA VECTOR DINAMICO (ENCOLADO) ----\n\n");
    cola_t* c= cola_crear();
    vector_t* vec1=vector_crear(5);
    vector_guardar(vec1, 0, 5);
    vector_guardar(vec1, 1, 3);
    vector_guardar(vec1, 2, 32);
    vector_guardar(vec1, 3, 34);
    vector_guardar(vec1, 4, 42);
    print_test("La cola fue creada", c != NULL);
    print_test("La cola esta vacia", cola_esta_vacia(c) == true);
    print_test("Ver primero en cola devuelve NULL", cola_ver_primero(c) == NULL);
    print_test("La cola fue encolada con valor vec1", cola_encolar(c,vec1) == true);
    print_test("La cola no esta vacia", !cola_esta_vacia(c) == true);
    cola_destruir(c,&vector_destruir_wrapper);
}

void prueba_vector_dinamico_enco_dese() {
	printf("----PRUEBA CON VECTOR DINAMICO(ENCOLADO Y DESENCOLADO) ----\n\n");
	cola_t* c= cola_crear();
	vector_t* vec1=vector_crear(2);
	vector_guardar(vec1, 0, 5);
	vector_guardar(vec1, 1, 3);
    print_test("La cola fue creada", c != NULL);
    print_test("La cola esta vacia", cola_esta_vacia(c) == true);
    print_test("Ver primero en cola devuelve NULL", cola_ver_primero(c) == NULL);
    print_test("La cola fue encolada con valor vec1", cola_encolar(c,vec1) == true);
    print_test("La cola no esta vacia", !cola_esta_vacia(c) == true);
    print_test("Desencolo el primero, devuelve vec1", cola_desencolar(c) == vec1);
    print_test("Ver primero en cola devuelve NULL", cola_ver_primero(c) == NULL);
    print_test("La cola esta vacia", cola_esta_vacia(c) == true);
    cola_destruir(c,NULL);
    vector_destruir(vec1);//Lo hace barbara ya que al desencolar pierdo referencia del nodo
}

void pila_destruir_wrapper(void* elem) {
	pila_destruir((pila_t*) elem);
}

void prueba_pila_encolar() {
	printf("----PRUEBA PILA (ENCOLADA) ----\n\n");
	cola_t* c= cola_crear();
	pila_t *p = pila_crear();
	char valor1='c';
	int valor2=22;
	int valor3[]={2,1,4,0};
	void* valor4=NULL;
	print_test("La pila fue creada", p != NULL);
   	print_test("La pila está vacía", pila_esta_vacia(p));
   	print_test("Apile en pila valor1, devuelve true",pila_apilar(p,&valor1) == true);
	print_test("Apile en pila valor2, devuelve true",pila_apilar(p,&valor2) == true);
	print_test("Apile en pila valor3, devuelve true",pila_apilar(p,&valor3) == true);
	print_test("Apile en pila valor4, devuelve true",pila_apilar(p,valor4) == true);

    print_test("La cola fue creada", c != NULL);
    print_test("La cola esta vacia", cola_esta_vacia(c) == true);
    print_test("Ver primero en cola devuelve NULL", cola_ver_primero(c) == NULL);
    print_test("La cola fue encolada con valor pila", cola_encolar(c,p) == true);
    print_test("La cola no esta vacia", !cola_esta_vacia(c) == true);
    cola_destruir(c,&pila_destruir_wrapper);
}

void prueba_pila_encolar_desencolar() {
    printf("----PRUEBA PILA (ENCOLADA Y DESENCOLADA) ----\n\n");
    cola_t* c= cola_crear();
    pila_t* p1 = pila_crear();
    char valor1='c';
    int valor2=22;
    int valor3[]={2,1,4,0};
    void* valor4=NULL;
    vector_t* valor5=vector_crear(2);
    vector_guardar(valor5, 0, 5);
    vector_guardar(valor5, 1, 3);

    print_test("La pila fue creada", p1 != NULL);
    print_test("La pila está vacía", pila_esta_vacia(p1));
    print_test("Apile en pila1 valor1, devuelve true",pila_apilar(p1,&valor1) == true);
    print_test("Apile en pila1 valor2, devuelve true",pila_apilar(p1,&valor2) == true);
    print_test("Apile en pila1 valor3, devuelve true",pila_apilar(p1,&valor3) == true);
    print_test("Apile en pila1 valor4, devuelve true",pila_apilar(p1,valor4) == true);
    print_test("Apile en pila1 valor5, devuelve true",pila_apilar(p1,valor5) == true);

    pila_t* p2 = pila_crear();
    void* valor6=NULL;
    int valor7=22;
    vector_t* valor8=vector_crear(2);
    vector_guardar(valor8, 0, 12);
    vector_guardar(valor8, 1, 978);
    int valor9[]={2,-1};

    print_test("La pila2 fue creada", p2 != NULL);
    print_test("La pila2 está vacía", pila_esta_vacia(p2));
    print_test("Apile en pila2 valor6, devuelve true",pila_apilar(p2,valor6) == true);
    print_test("Apile en pila2 valor7, devuelve true",pila_apilar(p2,&valor7) == true);
    print_test("Apile en pila2 valor8, devuelve true",pila_apilar(p2,valor8) == true);
    print_test("Apile en pila2 valor9, devuelve true",pila_apilar(p2,&valor9) == true);
   
    print_test("La cola fue creada", c != NULL);
    print_test("La cola esta vacia", cola_esta_vacia(c) == true);
    print_test("Ver primero en cola devuelve NULL", cola_ver_primero(c) == NULL);
    print_test("La cola fue encolada con valor pila1", cola_encolar(c,p1) == true);
    print_test("La cola fue encolada con valor pila2", cola_encolar(c,p2) == true);
    print_test("Ver primero en cola devuelve pila1", cola_ver_primero(c) == p1);
    print_test("Desencolo el primero, devuelve pila1", cola_desencolar(c) == p1);
    print_test("Desencolo el primero, devuelve pila2", cola_desencolar(c) == p2);
    print_test("La cola esta vacia", cola_esta_vacia(c) == true);
    print_test("Ver primero en cola devuelve NULL", cola_ver_primero(c) == NULL);
    cola_destruir(c,NULL);
    vector_destruir(valor5);
    vector_destruir(valor8);
    pila_destruir(p1);
    pila_destruir(p2);
}

void prueba_voluminosa() {
    printf("-----------PRUEBA CON GRAN CANTIDAD DE ELEMENTOS-----------\n");
    cola_t* c = cola_crear();
    print_test("La cola fue creada", c != NULL);
    print_test("La cola está vacía", cola_esta_vacia(c));
    int tam=5000;
    int vector[tam];
    for (int i=0; i<tam;i++) { //Lleno el vector
        vector[i]=i;
    }
    for (int i=0; i<tam;i++) {
        printf("Voy a encolar el numero: %d\n",i);
        print_test("Encole en cola numero, devuelve true",cola_encolar(c,&vector[i]) == true);
    }
    for (int i=0; i<tam;i++) {
        print_test("Desencolo la cola anterior, devuelve un numero",*(int*)cola_desencolar(c) == vector[i]);
        printf("El valor numerico es %d\n",vector[i]);
    }
    print_test("La cola está vacía", cola_esta_vacia(c));
    print_test("Desencolo una cola vacía, devuelve NULL",cola_desencolar(c) == NULL);
    print_test("Ver primero en cola desencolada hasta vacio, devuelve NULL",cola_ver_primero(c) == NULL);
    cola_destruir(c,NULL);
}

void cola_destruir_wrapper(void* elem) {
    cola_destruir((cola_t*) elem,&vector_destruir_wrapper);
}

void prueba_encolando_cola() {
    printf("----PRUEBA COLA ENCOLADA CON UNA COLA QUE TIENE VD----\n\n");
    vector_t* vec1=vector_crear(2);
    vector_guardar(vec1, 0, 12);
    vector_guardar(vec1, 1, 978);
    cola_t* c1 = cola_crear();
    print_test("La cola1 fue creada", c1 != NULL);
    print_test("La cola1 fue encolada con valor vec1", cola_encolar(c1,vec1) == true);

    cola_t *c2 = cola_crear();
    print_test("La cola2 fue creada", c2 != NULL);
    print_test("La cola2 esta vacia", cola_esta_vacia(c2) == true);
    print_test("La cola2 fue encolada con cola1", cola_encolar(c2,c1) == true);
    print_test("La cola2 no esta vacia", !cola_esta_vacia(c2) == true);
    print_test("Ver primero en cola2 devuelve cola1",cola_ver_primero(c2) == c1);
    cola_destruir(c2,&cola_destruir_wrapper);
}

void pruebas_cola_alumno(){
    prueba_cola_vacia();
    prueba_encolando_1_elemento();
	prueba_encolando_null();
	prueba_varios_tipos();
	prueba_vector_dinamico_encolado();
	prueba_vector_dinamico_enco_dese();
	prueba_pila_encolar();
    prueba_pila_encolar_desencolar();
    prueba_encolando_cola();
    prueba_voluminosa();
}


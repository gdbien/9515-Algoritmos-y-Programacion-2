#include "pila.h"
#include "vector_dinamico.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>

/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/

void pruebas_pila_vacia() {
	printf("-----------PRUEBAS CON PILA VACIA-----------\n");
	pila_t *p = pila_crear();
    print_test("La pila fue creada", p != NULL);
   	print_test("La pila está vacía", pila_esta_vacia(p));	
   	print_test("Desapilo una pila vacía, devuelve NULL",pila_desapilar(p) == NULL);
   	print_test("Ver tope en pila recien creada, devuelve NULL",pila_ver_tope(p) == NULL);
   	pila_destruir(p);
}

void prueba_crear_y_apilar_1_elemento() {
	printf("-----------PRUEBAS CON PILA RECIEN CREADA-----------\n");
	pila_t* ejemplo = NULL;
    print_test("Puntero inicializado a NULL", ejemplo == NULL);
    pila_t *p = pila_crear();

    print_test("La pila fue creada", p != NULL);
   	print_test("La pila está vacía", pila_esta_vacia(p));	
   	print_test("Desapilo una pila vacía, devuelve NULL",pila_desapilar(p) == NULL);
   	print_test("Ver tope en pila recien creada, devuelve NULL",pila_ver_tope(p) == NULL);
	
	int valor1=42;
	print_test("Apile en pila vacia, devuelve true",pila_apilar(p,&valor1) == true);
	print_test("Ver tope en pila, devuelve valor1",pila_ver_tope(p) == &valor1);
	print_test("El valor numerico del tope es efectivamente 42", valor1==42);
	print_test("La pila no está vacía", !pila_esta_vacia(p));
	print_test("Desapilo la pila anterior, devuelve 42",*(int*)pila_desapilar(p) == valor1);
	print_test("La pila está vacía", pila_esta_vacia(p));
   	pila_destruir(p);
}

void pruebas_vector_dinamico() {
	printf("----PRUEBAS VECTOR DINAMICO ----\n\n");
	pila_t *p = pila_crear();
	vector_t* vec1=vector_crear(2);
	vector_guardar(vec1, 0, 5);
	vector_guardar(vec1, 1, 3);

	vector_t* vec2=vector_crear(3);
	vector_guardar(vec2, 0, 42);
	vector_guardar(vec2, 1, 12);
	vector_guardar(vec2, 2, 32);

	int valor1,valor2,valor3,valor4,valor5;

    print_test("La pila fue creada", p != NULL);
   	print_test("La pila está vacía", pila_esta_vacia(p));	
    print_test("Ver tope en pila recien creada, devuelve NULL",pila_ver_tope(p) == NULL);
    print_test("Apile en pila vacia, devuelve true",pila_apilar(p,vec1) == true);
    print_test("La pila no está vacía", !pila_esta_vacia(p));
    print_test("Desapilo la pila anterior, devuelve vec1",pila_desapilar(p) == vec1);
    vector_obtener(vec1,0,&valor1);
    vector_obtener(vec1,1,&valor2);
    print_test("Los valores del vec1 no fueron alterados",valor1==5 && valor2==3);
    print_test("Ver tope en pila recien creada, devuelve NULL",pila_ver_tope(p) == NULL);
    print_test("La pila está vacía", pila_esta_vacia(p));
    print_test("Apile en pila vacia, devuelve true",pila_apilar(p,vec2) == true);
    print_test("Desapilo la pila anterior, devuelve vec2",pila_desapilar(p) == vec2);
    vector_obtener(vec2,0,&valor3);
    vector_obtener(vec2,1,&valor4);
	vector_obtener(vec2,2,&valor5);
	print_test("Los valores del vec2 no fueron alterados",valor3==42 && valor4==12 && valor5==32);
    print_test("La pila está vacía", pila_esta_vacia(p));
    pila_destruir(p);
    vector_destruir(vec1);
    vector_destruir(vec2);
}

void prueba_crear_y_apilar_NULL() {
	printf("-----------PRUEBAS APILANDO NULL's-----------\n");
	pila_t* ejemplo = NULL;
    print_test("Puntero inicializado a NULL", ejemplo == NULL);
    pila_t *p = pila_crear();
    print_test("La pila fue creada", p != NULL);
   	print_test("La pila está vacía", pila_esta_vacia(p));	
   	print_test("Desapilo una pila vacía, devuelve NULL",pila_desapilar(p) == NULL);
   	print_test("Ver tope en pila recien creada, devuelve NULL",pila_ver_tope(p) == NULL);
	
	void* valor1=NULL;
	int valor2=5;
	char valor3='a';

	print_test("Apile NULL en pila vacia, devuelve true",pila_apilar(p,valor1) == true);
	print_test("Ver tope en pila, devuelve  valor NULL",pila_ver_tope(p) == valor1);
	print_test("La pila no está vacía", !pila_esta_vacia(p));
	print_test("Apilo devuelta NULL, devuelve true",pila_apilar(p,valor1) == true);
	print_test("Desapilo la pila anterior, devuelve valor NULL",pila_desapilar(p) == valor1);
	print_test("Apilo valor2, devuelve true",pila_apilar(p,&valor2) == true);
	print_test("Apilo devuelta NULL, devuelve true",pila_apilar(p,valor1) == true);
	print_test("Ver tope en pila , devuelve valor NULL",pila_ver_tope(p) == valor1);
	print_test("Desapilo la pila anterior, devuelve valor NULL",pila_desapilar(p) == valor1);
	print_test("Ver tope en pila , devuelve valor2",pila_ver_tope(p) == &valor2);
	print_test("Desapilo la pila anterior, devuelve valor2",pila_desapilar(p) == &valor2);
	print_test("La pila no está vacía", !pila_esta_vacia(p));
	print_test("Desapilo la pila anterior, devuelve valor NULL",pila_desapilar(p) == valor1);
	print_test("La pila está vacía", pila_esta_vacia(p));
	print_test("Apilo valor3, devuelve true",pila_apilar(p,&valor3) == true);
	print_test("Desapilo la pila anterior, devuelve valor3",pila_desapilar(p) == &valor3);
	print_test("La pila está vacía", pila_esta_vacia(p));
	print_test("Desapilo una pila vacía, devuelve NULL",pila_desapilar(p) == NULL);
   	print_test("Ver tope en pila vacia, devuelve NULL",pila_ver_tope(p) == NULL);
   	print_test("Los valores apilados no fueron alterados",valor1==NULL &&  valor2==5 && valor3=='a');
   	pila_destruir(p);
}

void prueba_apilar_y_desapilar_varios_tipos() {
	printf("-----------PRUEBAS CON PILA, APILANDO/DESAPILANDO VARIOS TIPOS-----------\n");
	pila_t *p = pila_crear();
	print_test("La pila fue creada", p != NULL);
   	print_test("La pila está vacía", pila_esta_vacia(p));

	int valor1=5;
	char valor2='c';
	int valor3=22;
	int valor4[]={2,1,4,0};
	void* valor5=NULL;
	vector_t* vec1=vector_crear(2);
	vector_guardar(vec1, 0, 5);
	vector_guardar(vec1, 1, 3);
	
	print_test("Apile en pila vacia, devuelve true",pila_apilar(p,&valor1) == true);
	print_test("La pila no está vacía", !pila_esta_vacia(p));
	print_test("Ver tope en pila recien creada, devuelve valor1",pila_ver_tope(p) == &valor1);
	print_test("Desapilo la pila anterior, devuelve valor1",pila_desapilar(p) == &valor1);
	print_test("La pila está vacía", pila_esta_vacia(p));
	print_test("Apile en pila valor2, devuelve true",pila_apilar(p,&valor2) == true);
	print_test("Apile en pila valor3, devuelve true",pila_apilar(p,&valor3) == true);
	print_test("Apile en pila valor4, devuelve true",pila_apilar(p,&valor4) == true);
	print_test("Apile en pila valor5, devuelve true",pila_apilar(p,valor5) == true);
	print_test("Apile en pila vec1, devuelve true",pila_apilar(p,vec1) == true);
	print_test("Ver tope en pila , devuelve vec1",pila_ver_tope(p) == vec1);
	print_test("Desapilo la pila anterior, devuelve vec1",pila_desapilar(p) == vec1);
	print_test("Ver tope en pila , devuelve valor5",pila_ver_tope(p) == valor5);
	print_test("Desapilo la pila anterior, devuelve valor5",pila_desapilar(p) == valor5);
	print_test("Ver tope en pila, devuelve valor4",pila_ver_tope(p) == &valor4);
	print_test("Desapilo la pila anterior, devuelve valor4",pila_desapilar(p) == &valor4);
	print_test("Ver tope en pila, devuelve valor3",pila_ver_tope(p) == &valor3);
	print_test("Desapilo la pila anterior, devuelve valor3",pila_desapilar(p) == &valor3);
	print_test("Ver tope en pila, devuelve valor2",pila_ver_tope(p) == &valor2);
	print_test("Desapilo la pila anterior, devuelve valor2",pila_desapilar(p) == &valor2);
	print_test("Desapilo la pila anterior(vacia), devuelve NULL",pila_desapilar(p) == NULL);
	print_test("La pila está vacía", pila_esta_vacia(p));
	print_test("Desapilo una pila vacía, devuelve NULL",pila_desapilar(p) == NULL);
   	print_test("Ver tope en pila desapilada hasta vacio, devuelve NULL",pila_ver_tope(p) == NULL);
	pila_destruir(p);
	vector_destruir(vec1);
}

void prueba_voluminosa() {
	printf("-----------PRUEBAS CON GRAN CANTIDAD DE ELEMENTOS-----------\n");
	pila_t *p = pila_crear();
	print_test("La pila fue creada", p != NULL);
   	print_test("La pila está vacía", pila_esta_vacia(p));
   	int tam=5000;
	int vector[tam];
	for (int i=0; i<tam;i++) { //Lleno el vector
		vector[i]=i;
	}
	for (int i=0; i<tam;i++) {
		print_test("Apile en pila valor i, devuelve true",pila_apilar(p,&vector[i]) == true);
	}
	for (int i=tam-1; i>=0;i--) {
		print_test("Desapilo la pila anterior, devuelve valor i",*(int*)pila_desapilar(p) == vector[i]);
		printf("El valor numerico es %d\n",vector[i]);
	}
	print_test("La pila está vacía", pila_esta_vacia(p));
	print_test("Desapilo una pila vacía, devuelve NULL",pila_desapilar(p) == NULL);
   	print_test("Ver tope en pila desapilada hasta vacio, devuelve NULL",pila_ver_tope(p) == NULL);
	pila_destruir(p);
}

void pruebas_pila_alumno() {
	pruebas_pila_vacia();
    prueba_crear_y_apilar_1_elemento();
    pruebas_vector_dinamico();
    prueba_crear_y_apilar_NULL();
   	prueba_apilar_y_desapilar_varios_tipos();
   	prueba_voluminosa();
}






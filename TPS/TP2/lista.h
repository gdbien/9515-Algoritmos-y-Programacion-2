#ifndef LISTA_H
#define LISTA_H

#include<stdbool.h>
#include<stddef.h>

/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

typedef struct lista lista_t;
typedef struct lista_iter lista_iter_t;

/* ******************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/

/*
* Crea una lista.
* Post: devuelve una nueva lista vacía.
*/
lista_t *lista_crear(void);

/*
* Devuelve verdadero o falso según si la lista tiene elementos o no.
* Pre: la lista fue creada.
*/
bool lista_esta_vacia(const lista_t *lista);

/*
* Agrega un nuevo elemento al inicio de la lista. Devuelve falso en caso de error.
* Pre: la lista fue creada.
* Post: se agregó un nuevo elemento a la lista, dato se encuentra al inicio.
*/
bool lista_insertar_primero(lista_t *lista, void *dato);

/*
* Agrega un nuevo elemento al final de la lista. Devuelve falso en caso de error.
* Pre: la lista fue creada.
* Post: se agregó un nuevo elemento a la lista, dato se encuentra al final.
*/
bool lista_insertar_ultimo(lista_t *lista, void *dato);

/*
* Saca el primer elemento de la lista.
* Si la lista tiene elementos saca el primero de la lista y devuelve su valor.
* Si la lista está vacía devuelve NULL.
* Pre: la lista fue creada.
* Post: se devolvió el dato del primer elemento de la lista y la lista
* contiene un elemento menos, si esta no está vacía.
*/
void *lista_borrar_primero(lista_t *lista);

/*
* Obtiene el dato del primer elemento de la lista.
* Si la lista tiene elementos devuelve el dato del primero.
* Si está vacía devuelve NULL.
* Pre: la lista fue creada.
* Post: se devolvió el dato del primer elemento de la lista, si esta no está vacía.
*/
void *lista_ver_primero(const lista_t *lista);

/*
* Obtiene el dato del último elemento de la lista.
* Si la lista tiene elementos devuelve el dato del último.
* Si está vacía devuelve NULL.
* Pre: la lista fue creada.
* Post: se devolvió el dato del último elemento de la lista, si esta no está vacía.
*/
void *lista_ver_ultimo(const lista_t* lista);

/*
* Devuelve el largo de la lista.
* Pre: la lista fue creada.
*/
size_t lista_largo(const lista_t *lista);

/*
* Destruye la lista.
* Si se recibe por parámetro la función destruir_dato se la llama para cada uno
* de los elementos de la lista.
* Pre: La lista fue creada. La función destruir_dato es capaz de destruir los
* datos de la lista, o NULL en caso de que no se la utilice.
* Post: se eliminaron todos los elementos de la lista.
*/
void lista_destruir(lista_t *lista, void destruir_dato(void *));

/* ******************************************************************
 *                  PRIMITIVAS DEL ITERADOR INTERNO
 * *****************************************************************/

/*
* Itera sobre la lista aplicando visitar a los elementos de esta,
* la iteración se corta si visitar devuelve false. Si visitar es NULL no se
* modifican los elementos de la lista.
* Pre: la lista fue creada.
* Post: se iteró sobre la lista aplicando visitar a cada elemento de esta.
*/
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra);

/* ******************************************************************
 *                 PRIMITIVAS DEL ITERADOR EXTERNO
 * *****************************************************************/

/*
* Crea un iterador.
* Pre: la lista fue creada.
* Post: devuelve un iterador o NULL en caso de error.
* Si la lista tiene elementos este apunta al primero, sino estará apuntando al final.
*/
lista_iter_t *lista_iter_crear(lista_t *lista);

/*
* Avanza el iterador un elemento en la lista.
* Pre: el iterador fue creado.
* Post: se avanzó el iterador un elemento en la lista si este no estaba apuntando
* al final de esta. Se devuelve verdadero si se pudo avanzar, falso en caso contrario.
*/
bool lista_iter_avanzar(lista_iter_t *iter);

/*
* Obtiene el dato del elemento en el que se esta parado actualmente.
* Pre: el iterador fue creado.
* Post: se devolvió el dato del elemento en el que se estaba parado, NULL en caso de error.
*/
void *lista_iter_ver_actual(const lista_iter_t *iter);

/*
* Pre: el iterador fue creado.
* Post: devuelte verdadero si el iterador se encuentra al final de la lista,
* falso en caso contrario.
*/
bool lista_iter_al_final(const lista_iter_t *iter);

/*
* Destruye el iterador.
* Pre: el iterador fue creado.
* Post: el iterador fue destruído.
*/
void lista_iter_destruir(lista_iter_t *iter);

/*
* Inserta un elemento en el lugar en el que se esta parado.
* Pre: el iterador fue creado.
* Post: se insertó un nuevo elemento en el lugar donde estaba parado el iterador,
* se devuelve verdadero si se pudo insertar el elemento.
* Se devuelve falso en caso de no haberse podido insertar el elemento.
*/
bool lista_iter_insertar(lista_iter_t *iter, void *dato);

/*
* Borra el elemento en el que se esta parado.
* Pre: el iterador fue creado.
* Post: el elemento al cual se estaba apuntando fue borrado, se devuelve el dato.
* O NULL en caso de que el iterador no apunte a un elemento válido de la lista.
*/
void *lista_iter_borrar(lista_iter_t *iter);

/* *****************************************************************
 *                      PRUEBAS UNITARIAS
 * *****************************************************************/

/*
* Realiza pruebas sobre la implementación.
*/
void pruebas_lista_alumno(void);

#endif //LISTA_H

#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stdlib.h>

/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

/* La lista está planteada como una lista de punteros genéricos. */

struct lista;
typedef struct lista lista_t;
typedef struct lista_iter lista_iter_t;


/* ******************************************************************
 *                    PRIMITIVAS DE LA COLA
 * *****************************************************************/

// Crea una lista.
// Post: devuelve una nueva lista vacía.
lista_t *lista_crear(void);

// Destruye la lista. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la lista llama a destruir_dato.
// Pre: la lista fue creada. destruir_dato es una función capaz de destruir
// los datos de la lista, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t *lista, void destruir_dato(void *));

// Devuelve verdadero o falso, según si la lista tiene o no elementos enlazados.
// Pre: la lista fue creada.
// Post: True si tiene elementos, False si esta vacia.
bool lista_esta_vacia(const lista_t *lista);

// Agrega un nuevo elemento al final de la lista. Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento a la lista, valor se encuentra al final
// de la lista.
bool lista_insertar_ultimo(lista_t *lista, void *dato);

// Agrega un nuevo elemento al principio de la lista. Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento a la lista, valor se encuentra al principio
// de la lista.
bool lista_insertar_primero(lista_t *lista, void *dato);

// Obtiene el valor del primer elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del primero, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el primer elemento de la lista, cuando no está vacía.
void *lista_ver_primero(const lista_t *lista);

// Obtiene el valor del ultimo elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del ultimo, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el ultimo elemento de la lista, cuando no está vacía.
void *lista_ver_ultimo(const lista_t* lista);

// Devuelve el largo de la lista(cantidad de elemento que tiene)
// Pre: la lista fue creada.
// Post: se devolvio el largo de la lista, 0 si esta vacia.
size_t lista_largo(const lista_t *lista);

// Saca el primer elemento de la lista. Si la lista tiene elementos, se quita el
// primero de la lista, y se devuelve su valor, si está vacía, devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el valor del primer elemento anterior, la lista
// contiene un elemento menos, si la lista no estaba vacía.
void *lista_borrar_primero(lista_t *lista);


/* ******************************************************************
 *                    PRIMITIVAS DEL ITERADOR INTERNO
 * *****************************************************************/


void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra);


/* ******************************************************************
 *                    PRIMITIVAS DEL ITERADOR EXTERNO
 * *****************************************************************/

// Crea una iterador externo.
// Pre: Lista creada.(no tiene sentido crear un iterador sin su lista).
// Post: devuelve un iterador externo apuntando al primer elemento de la lista
// si tiene elementos, en caso contrario, apunta al final de la lista.
lista_iter_t *lista_iter_crear(lista_t *lista);

// Avanza el iterador al proximo elemento
// Pre: el iterador fue creado.
// Post: devolvio true si pudo avanzar el iterador, y false, en caso contrario.
bool lista_iter_avanzar(lista_iter_t *iter);

// Obtiene el valor del elemento actual al cual apunta el iterador. Si la lista esta vacia,
// devuelve NULL.
// Pre: el iterador fue creado.
// Post: se devolvió el valor del elemento de la posicion actual del iterador.
void *lista_iter_ver_actual(const lista_iter_t *iter);

// Devuelve verdadero si el iterador se encuentra en el ultimo elemento de la lista,
// y falso, en caso contrario.
// Pre: el iterador fue creado.
bool lista_iter_al_final(const lista_iter_t *iter);

// Destruye el iterador.
// Pre: el iterador fue creado.
// Post: el iterador fue eliminado.
void lista_iter_destruir(lista_iter_t *iter);

// Agrega un nuevo elemento a la lista. Devuelve falso en caso de error.
// Pre: el iterador fue creado.
// Post: se agregó un nuevo elemento a la lista, dato se encuentra en la posicion
// agregada.
bool lista_iter_insertar(lista_iter_t *iter, void *dato);

// Destruye el nodo actual al cual apunta el iterador.
// Pre: el iterador fue creado.
// Post: el nodo al cual el iterador apuntaba fue destruido.
void *lista_iter_borrar(lista_iter_t *iter);

/* *****************************************************************
 *                      PRUEBAS UNITARIAS
 * *****************************************************************/

// Realiza pruebas sobre la implementación del alumno.
//
// Las pruebas deben emplazarse en el archivo ‘pruebas_alumno.c’, y
// solamente pueden emplear la interfaz pública tal y como aparece en lista.h
// (esto es, las pruebas no pueden acceder a los miembros del struct lista).
//
// Para la implementación de las pruebas se debe emplear la función
// print_test(), como se ha visto en TPs anteriores.
void pruebas_lista_alumno(void);

#endif // LISTA_H
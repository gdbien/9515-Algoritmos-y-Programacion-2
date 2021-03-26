#ifndef ABB_H
#define ABB_H
#include <stdbool.h>
#include <stdlib.h>
typedef struct abb abb_t;
typedef struct abb_iter abb_iter_t;

typedef int (*abb_comparar_clave_t) (const char *, const char *);
typedef void (*abb_destruir_dato_t) (void *);

/******************** PRIMITIVAS ABB ********************/
// Crea el arbol.
// Post: Se creo el arbol.
abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato);

// Pre: El arbol fue creado.
// Post: Guarda en el arbol la clave y el dato, si la clave ya existia, reemplaza el dato anterior con el nuevo dato.
bool abb_guardar(abb_t *arbol, const char *clave, void *dato);

// Pre: El arbol fue creado.
// Post: Elimina una clave del arbol y devuelve su dato, si la clave no existe, devuelve NULL.
void *abb_borrar(abb_t *arbol, const char *clave);

// Pre: El arbol fue creado.
// Post: Devuelve el dato de la clave, si la clave no existe, devuelve NULL.
void *abb_obtener(const abb_t *arbol, const char *clave);

// Pre: El arbol fue creado.
// Post: Devuelve true si la clave existe, en caso contrario, devuelve false.
bool abb_pertenece(const abb_t *arbol, const char *clave);

// Pre: EL arbol fue creado.
// Post: Devuelve la cantidad de claves que tiene un arbol.
size_t abb_cantidad(abb_t *arbol);

// Pre: El arbol fue creado.
// Post: Se destruyo el arbol en su totalidad.
void abb_destruir(abb_t *arbol);

/******************** ITERADOR INTERNO ********************/
// Pre: El arbol fue creado.
// Post: Recorre el arbol en el seguimiento INORDER, "visitando" su contenido.
void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra);

/******************** ITERADOR EXTERNO ********************/
// Pre: El arbol fue creado.
// Post: Se creo el iterador.
abb_iter_t *abb_iter_in_crear(const abb_t *arbol);

// Pre: El iterador fue creado.
// Post: Devuelve true si avanzo el iterador, en caso contrario, devuelve false.
bool abb_iter_in_avanzar(abb_iter_t *iter);

// Pre: El iterador fue creado.
// Post: Devuelve la clave a la cual esta apuntando, si esta al final, devuelve NULL.
const char *abb_iter_in_ver_actual(const abb_iter_t *iter);

// Pre: El iterador fue creado.
// Post: Devuelve true si esta al final, en caso contrario, devuelve false.
bool abb_iter_in_al_final(const abb_iter_t *iter);

// Pre: El iterador fue creado.
// Post: Se destruyo el iterador en su totalidad.
void abb_iter_in_destruir(abb_iter_t* iter);

#endif // ABB_H

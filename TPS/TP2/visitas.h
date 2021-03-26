#ifndef VISITAS_H
#define VISITAS_H

#include "hash.h"

typedef struct visitantes visitantes_t;

/*
* Crea visitantes.
* Post: devuelve el <visitantes> creado, o NULL en caso de error.
*/
visitantes_t* visitantes_crear();

/*
* Destruye <visitantes>.
* Pre: <visitantes> fue creado.
* Post: se liberó toda memoria usada por <visitantes>.
*/
void visitantes_destruir(visitantes_t* visitantes);

/*
* Agrega un nuevo elemento a <visitantes>.
* Pre: <visitantes> fue creado.
* Post: se agregó un nuevo elemento a <visitantes>, con los datos pasados.
* Se devuleve false en caso de error, true en caso contrario.
*/
bool agregar_visitante(visitantes_t* visitantes, const char* ip_nuevo, char* sitio);

/*
* Imprime los visitantes en un rango determinado.
* Pre: <visitantes> fue creado. <desde> y <hasta> son ips.
* Post: se imprimieron todas las ips de los visitantes que entran en el rango
* determinado por <desde> y <hasta> (en orden ascendente).
* Se devuelve false en caso de error, true en caso contrario.
*/
bool imprimir_visitantes_desde_hasta(visitantes_t* visitantes, char* desde, char* hasta);

/*
* Imprime los sitios más visitados.
* Pre: <visitantes> fue creado.
* Post: se imprimieron los <cantidad> de sitios más visitados (en orden
* descendente según la cantidad de visitas).
* Se devuelve false en caso de error, true en caso contrario.
*/
bool imprimir_mas_visitados(visitantes_t* visitantes, size_t cantidad);

#endif // VISITAS_H

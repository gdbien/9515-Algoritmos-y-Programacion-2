#ifndef ANALOG_H
#define ANALOG_H

#include <stdbool.h>
#include "visitas.h"

/*
* Procesa un archivo de log.
* Pre: visitantes fue creado.
* Post: se agregó el archivo <file_name> y se imprimieron las ip sospechosas
* de un ataque DoS.
* Se devuelve false en caso de error, true en caso contrario.
*/
bool agregar_archivo(char* file_name, visitantes_t* visitantes);

/*
* Muestra las IP que solicitaron algún recurso al servidor, entre el rango determinado.
* Pre: visitantes fue creado. <desde> y <hasta> son ips.
* Post: se imprimieron todos los ips dentro del rango que alguna vez realizaron
* alguna petición.
* Se devuelve false en caso de error, true en caso contrario.
*/
bool ver_visitantes(visitantes_t* visitantes, char* desde, char* hasta);

/*
* Muestra los <cantidad> recursos más visitados.
* Pre: visitantes fue creado.
* Post: se imprimieron los <cantidad> de recursos más visitados.
* Se devuelve false en caso de error, true ne caso contrario.
*/
bool ver_mas_visitados(size_t cantidad, visitantes_t* visitantes);

#endif // ANALOG_H

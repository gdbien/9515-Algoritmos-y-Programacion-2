#ifndef IP_H
#define IP_H

#include "lista.h"
#include "abb.h"

typedef struct ip_info ip_info_t;

/*
* Compara dos ips.
* Post: devuelve un int, según el siguiente criterio:
*   menor a cero, si <ip1> < <ip2>.
*   mayor a cero, si <ip1> > <ip2>.
*   igual a cero, si <ip1> == <ip2>.
*/
int cmp_ip(const char* ip1, const char* ip2);

/*
* Crea <ip_info>.
* Post: devuelve el <ip_info> creado, o NULL en caso de error.
*/
ip_info_t* ip_info_crear();

/*
* Destruye el <ip_info>.
* Pre: el <ip_info> fue creado.
* Post: se liberó toda memoria usada por el <ip_info>.
*/
void ip_info_destruir(ip_info_t* ip_info);

/*
* Inserta un horario de visita en el <ip_info>.
* Pre: el <ip_info> fue creado.
* Post: se insertó un horario de visita.
* se devuelve false en caso de error, true en caso contrario.
*/
bool ip_info_insertar(ip_info_t* ip_info, char* horario);

/*
* Pre: el <ip_info> fue creado.
* Post: se devuelve el primer horario de visita insertado.
* Devuelve NULL en caso de error.
*/
void* ip_info_ver_primero(ip_info_t* ip_info);

/*
* Borra el primero.
* Pre: el <ip_info> fue creado.
* Post: el primero fue sacado del <ip_info> y se lo devolvió.
* Devuelve NULL en caso de error, o que no haya un primero a borrar.
*/
void* ip_info_borrar_primero(ip_info_t* ip_info);

/*
* Verifica si está vacío.
* Pre: el <ip_info> fue creado.
* Post: se devuelve true si está vacío, false en caso contrario.
*/
bool ip_info_esta_vacio(ip_info_t* ip_info);

/*
* Verifica si es un posible DoS.
* Pre: el <ip_info> fue creado.
* Post: devuelve true si el ip está realizando un posible ataque DoS, false
* en caso contrario.
*/
bool ip_info_es_dos(ip_info_t* ip_info);

#endif // IP_H

#ifndef DOS_H
#define DOS_H

#include "abb.h"
#include "hash.h"

/*
* Va detectando posibles DoS por cada línea.
* Pre: el hash y el abb fueron creados. strv contiene la línea actual del
* archivo en un array.
* Post: si la visita leída en la línea actual implica que un ip realizó
* cinco o más pedidos en menos de dos segundos, entonces se suma ese ip
* a los <posibles_dos>.
* Se devuelve false en caso de error, true en caso contrario.
*/
bool detectar_dos_linea(char** strv, hash_t* visitas, abb_t* posibles_dos);

/*
* Imprime los posibles DoS detectados.
* Pre: el abb fue creado y contiene los ip que realizaron posibles DoS.
* Post: se imprimieron los ip que realizaron posibles DoS.
*/
void imprimir_ips_dos(abb_t* posibles_dos);

#endif // DOS_H

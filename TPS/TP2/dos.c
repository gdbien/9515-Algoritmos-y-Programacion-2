#define _POSIX_C_SOURCE 200809L //getline

#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "abb.h"
#include "hash.h"
#include "strutil.h"
#include "timeutils.h"
#include "ip.h"

/******************** PRIMITIVAS DOS ********************/

bool detectar_dos_linea(char** strv, hash_t* hash, abb_t* abb) {
  char* ip = strv[0];
  char* horario;
  ip_info_t* ip_info = hash_obtener(hash, ip);
  if(!ip_info) {
    horario = strdup(strv[1]);
    if(!horario) return false;
    ip_info = ip_info_crear();
    if(!ip_info) {
      free(horario);
      return false;
    }
    ip_info_insertar(ip_info, horario);
    if(!hash_guardar(hash, ip, ip_info)) {
      abb_destruir(abb);
      hash_destruir(hash);
      return false;
    }
  }
  else {
    if(!ip_info_es_dos(ip_info)) {
      horario = strdup(strv[1]);
      time_t primero = iso8601_to_time(ip_info_ver_primero(ip_info));
      time_t ultimo = iso8601_to_time(horario);
      ip_info_insertar(ip_info, horario);
      while(!ip_info_esta_vacio(ip_info) && difftime(ultimo, primero) >= 2) {
        free(ip_info_borrar_primero(ip_info));
        primero = iso8601_to_time(ip_info_ver_primero(ip_info));
      }
      if(ip_info_es_dos(ip_info)) abb_guardar(abb, ip, NULL);
    }
  }
  return true;
}

void imprimir_ips_dos(abb_t* abb) {
  abb_iter_t* iter = abb_iter_in_crear(abb);
  while(!abb_iter_in_al_final(iter)) {
    fprintf(stdout,"DoS: %s\n", abb_iter_in_ver_actual(iter));
    abb_iter_in_avanzar(iter);
  }
  abb_iter_in_destruir(iter);
}

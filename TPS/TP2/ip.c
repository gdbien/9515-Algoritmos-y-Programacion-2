#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "lista.h"
#include "abb.h"
#include "ip.h"
#include "strutil.h"

#define SEPARADOR_IP '.'
#define CMP_IGUAL 0
#define CMP_MENOR -1
#define CMP_MAYOR 1
#define LARGO_DOS 5

struct ip_info {
  lista_t* time_requests;
};

/******************** PRIMITIVAS IP ********************/

ip_info_t* ip_info_crear() {
  ip_info_t* ip_info = malloc(sizeof(ip_info_t));
  if(!ip_info) return NULL;
  ip_info->time_requests = lista_crear();
  if(!ip_info->time_requests) {
    free(ip_info);
    return NULL;
  }
  return ip_info;
}

void ip_info_destruir(ip_info_t* ip_info) {
  lista_destruir(ip_info->time_requests, free);
  free(ip_info);
}

int cmp_ip(const char* ip1, const char* ip2) {
  char** strv_ip1 = split(ip1, SEPARADOR_IP);
  char** strv_ip2 = split(ip2, SEPARADOR_IP);
  size_t i = 0;
  while(strv_ip1[i] && strv_ip2[i]) {
    size_t numero_ip1 = atol(strv_ip1[i]);
    size_t numero_ip2 = atol(strv_ip2[i]);
    if(numero_ip1 < numero_ip2) {
      free_strv(strv_ip1);
      free_strv(strv_ip2);
      return CMP_MENOR;
    }
    if(numero_ip1 > numero_ip2) {
      free_strv(strv_ip1);
      free_strv(strv_ip2);
      return CMP_MAYOR;
    }
    i++;
  }
  free_strv(strv_ip1);
  free_strv(strv_ip2);
  return CMP_IGUAL;
}

bool ip_info_insertar(ip_info_t* ip_info, char* horario) {
  return lista_insertar_ultimo(ip_info->time_requests, horario);
}

void* ip_info_ver_primero(ip_info_t* ip_info) {
  return lista_ver_primero(ip_info->time_requests);
}

void* ip_info_borrar_primero(ip_info_t* ip_info) {
  return lista_borrar_primero(ip_info->time_requests);
}

bool ip_info_esta_vacio(ip_info_t* ip_info) {
  return lista_esta_vacia(ip_info->time_requests);
}

bool ip_info_es_dos(ip_info_t* ip_info) {
  return lista_largo(ip_info->time_requests) == LARGO_DOS;
}

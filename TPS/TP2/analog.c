#define _POSIX_C_SOURCE 200809L //getline

#include <stdio.h>
#include <stdlib.h>
#include "analog.h"
#include "dos.h"
#include "abb.h"
#include "strutil.h"
#include "ip.h"

#define SEPARADOR_LINEA '\t'

void ip_info_destruir_wrapper(void* elem) {
  ip_info_destruir((ip_info_t*)elem);
}

/******************** PRIMITIVAS ANALOG ********************/

bool agregar_archivo(char* file_name, visitantes_t* visitantes) {
  FILE* archivo_logs = fopen(file_name, "r");
  if(!archivo_logs) return false;
  hash_t* hash = hash_crear(ip_info_destruir_wrapper);
  abb_t* abb = abb_crear(*cmp_ip, NULL);
  char* linea = NULL; size_t capacidad = 0; ssize_t leidos;
  while((leidos = getline(&linea, &capacidad, archivo_logs)) > 0) {
    linea[leidos-1] = '\0';
    char** strv = split(linea,SEPARADOR_LINEA);
    if(!strv) {
      free(linea);
      fclose(archivo_logs);
      return false;
    }
    if(!detectar_dos_linea(strv, hash, abb)) {
      abb_destruir(abb);
      hash_destruir(hash);
      free(linea);
      fclose(archivo_logs);
      free_strv(strv);
      return false;
    }
    agregar_visitante(visitantes, strv[0], strv[3]);
    free_strv(strv);
  }
  imprimir_ips_dos(abb);
  hash_destruir(hash);
  abb_destruir(abb);
  free(linea);
  fclose(archivo_logs);
  return true;
}

bool ver_visitantes(visitantes_t* visitantes, char* desde, char* hasta) {
  printf("Visitantes:\n");
  return imprimir_visitantes_desde_hasta(visitantes, desde, hasta);
}

bool ver_mas_visitados(size_t cantidad, visitantes_t* visitantes) {
  printf("Sitios más visitados:\n");
  return imprimir_mas_visitados(visitantes, cantidad);
}

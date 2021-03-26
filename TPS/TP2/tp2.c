#define _POSIX_C_SOURCE 200809L //getline

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "strutil.h"
#include "analog.h"
#include "visitas.h"

#define AGREGAR_ARCHIVO "agregar_archivo"
#define VER_VISITANTES "ver_visitantes"
#define VER_MAS_VISITADOS "ver_mas_visitados"
#define PARAMETROS_AGREGAR_ARCHIVO 2
#define PARAMETROS_VER_VISITANTES 3
#define PARAMETROS_VER_MAS_VISITADOS 2
#define SEPARADOR_PARAMETROS ' '

size_t calcular_parametros(char** comando);
bool es_un_numero(char* cadena);

/******************** PROGRAMA PRINCIPAL ********************/

int main(int argc, char const *argv[]) {
  visitantes_t* visitantes = visitantes_crear();
  char* linea = NULL;
  size_t capacidad = 0;
  while(getline(&linea, &capacidad, stdin) > 0) {
    linea[strlen(linea)-1] = '\0';
    char** comando = split(linea, SEPARADOR_PARAMETROS);
    if(!comando) {
      free(linea);
      visitantes_destruir(visitantes);
      return 0;
    }
    bool ok = true;
    size_t cant_parametros = calcular_parametros(comando);
    if(strcmp(comando[0], AGREGAR_ARCHIVO) == 0 && cant_parametros == PARAMETROS_AGREGAR_ARCHIVO) {
      ok &= agregar_archivo(comando[1], visitantes);
    }
    else if(strcmp(comando[0], VER_VISITANTES) == 0 && cant_parametros == PARAMETROS_VER_VISITANTES) {
      char* desde = comando[1];
      char* hasta = comando[2];
      ok &= ver_visitantes(visitantes, desde, hasta);
    }
    else if(strcmp(comando[0], VER_MAS_VISITADOS) == 0 && cant_parametros == PARAMETROS_VER_MAS_VISITADOS && es_un_numero(comando[1])) {
      size_t cantidad = atol(comando[1]);
      ok &= ver_mas_visitados(cantidad, visitantes);
    }
    else {
      fprintf(stderr, "Error en comando %s\n", comando[0]);
      free(linea);
      visitantes_destruir(visitantes);
      free_strv(comando);
      return 0;
    }

    ok ? printf("OK\n") : fprintf(stderr, "Error en comando %s\n", comando[0]);

    free_strv(comando);
  }
  free(linea);
  visitantes_destruir(visitantes);
  return 0;
}

/******************** FUNCIONES AUXILIARES ********************/

size_t calcular_parametros(char** comando) {
  size_t parametros = 0;
  while(comando[parametros]) parametros++;
  return parametros;
}

bool es_un_numero(char* cadena) {
  size_t i = 0;
  while(cadena[i]) {
    if((cadena[i] > '9' ||  cadena[i] < '0') && cadena[i] != '.') return false;
    i++;
  }
  return true;
}

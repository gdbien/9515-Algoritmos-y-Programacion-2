#define _GNU_SOURCE 1 //Para usar strdup y strsep

#include <stdlib.h>
#include <string.h>
#include "strutil.h"

#define CARATER_CORTE '\0'

/*
 * Devuelve en un arreglo dinámico terminado en NULL con todos los subsegmentos
 * de ‘str’ separados por el carácter ‘sep’. Tanto el arreglo devuelto como las
 * cadenas que contiene son allocadas dinámicamente.
 *
 * Quien llama a la función toma responsabilidad de la memoria dinámica del
 * arreglo devuelto. La función devuelve NULL si falló alguna llamada a
 * malloc(), o si ‘sep’ es '\0'.
 */

char** crear_arreglo_dinamico(size_t tam) {
	char** strv=malloc(sizeof(char*)*tam); // Como minimo 2 ya que voy a tener NULL + string vacio
	if (!strv) {
		return NULL;
	}
	return strv;
}

size_t contador_separadores(const char* str, char sep) {
	size_t largo=strlen(str);
	size_t cantidad_separador=0;
	for (size_t i=0;i<largo;i++) {
		if(str[i]==sep) {
			cantidad_separador++;
		}
	}
	return cantidad_separador;
}

 char** split(const char* str, char sep) {
 	char separador[]={sep,CARATER_CORTE}; //Strsep usa el separador como string
	if (sep==CARATER_CORTE) {
		return NULL;
	}
	size_t cantidad_separador=contador_separadores(str,sep);
	size_t largo_strv=cantidad_separador+2;
	char** strv=crear_arreglo_dinamico(largo_strv);
	if (!strv) {
		return NULL;
	}
	char* str_copia=strdup(str);
	char* string=str_copia;
	char* aux=str_copia; 
	size_t i=0;
	while (string != NULL) {
		strsep(&aux,separador);
		strv[i]=strdup(string);
		string=aux;
		i++;
	}
	strv[i]=NULL;
	free(str_copia);
	return strv;
}

void free_strv(char** strv) {
	size_t i=0;
	while (strv[i]!=NULL) {
		free(strv[i]);
		i++;
	}
	free(strv);
}
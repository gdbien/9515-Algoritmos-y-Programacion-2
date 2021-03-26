#ifndef FUNCIONES_AUX
#define FUNCIONES_AUX
#include <stdbool.h>
#include <stdlib.h>

bool son_iguales(char* str1, char* str2);

bool es_double_valido(char* string, double* valor);

bool es_un_digito(char dato);

bool es_sizet_valido(char* string, size_t* valor);

size_t obtener_cantidad_lineas(const char* file_name);

void reemplazar_caracter_corte(char* string,char caracter);

#endif
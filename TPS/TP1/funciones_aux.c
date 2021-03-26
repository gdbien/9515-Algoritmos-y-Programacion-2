#include <string.h>
#include <errno.h>
#include <stdio.h>
#include "funciones_aux.h"

#define CARATER_CORTE '\0'

// Reemplaza la primera aparicion del caracter con '\0'
void reemplazar_caracter_corte(char* string,char caracter) {
	size_t len=strlen(string);
	size_t i=0;
	while (i<len) {
		if (string[i]==caracter) {
			string[i]=CARATER_CORTE;
			return;
		}
		i++;
	}
}

bool son_iguales(char* str1, char* str2) {
	return strcmp(str1,str2)==0;
}

bool es_double_valido(char* string, double* valor) {
	char* fin=string;
	errno=0;
	*valor=strtod(string,&fin);
	if (errno!=0 || fin==string || *fin!='\0') return false;
	return true;
}

bool es_un_digito(char dato) {
	return dato=='9' || dato=='8' || dato=='7' || dato=='6' || dato=='5' || dato=='4' || dato=='3' || dato=='2' || dato=='1' || dato=='0';
}

bool es_sizet_valido(char* string, size_t* valor) {
	size_t len=strlen(string);
	bool hayerror=false;
	size_t i=0;
	while (i<len && !hayerror) {
		if (!es_un_digito(string[i])) hayerror=true;
		i++;
	}
	if (!hayerror && len>0) {
		*valor=strtoul(string,NULL,10);
		return true;
	}
	return false;
}

size_t obtener_cantidad_lineas(const char* file_name) {
    size_t cantidad_lineas=0;
    FILE* f_archivo=fopen(file_name,"r");
    if (!f_archivo){
        fprintf(stderr,"No se encontro el archivo de cuentas");
        return 0;
    }
    int ch;
    int letras_en_linea = 0;

    while ((ch = fgetc(f_archivo)) != EOF) {
        if (ch == '\n') {
            cantidad_lineas++;
            letras_en_linea = 0;
        } else {
            letras_en_linea++;
        }
    }
    if (letras_en_linea > 0) {
        cantidad_lineas++;
    }
    fclose(f_archivo);
    return cantidad_lineas;
}

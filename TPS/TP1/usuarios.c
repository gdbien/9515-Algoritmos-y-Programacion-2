#define _GNU_SOURCE 1
#include <string.h>
#include "strutil.h"
#include "usuarios.h"
#include "funciones_aux.h"

#define SALTO_DE_LINEA '\n'

vector_t* crear_vd_usuarios(size_t cantidad, FILE* f_archivo) {
	char* linea = NULL; size_t capacidad = 0; ssize_t leidos; //combo getline
    size_t indice=0;
    vector_t* vector=vector_crear(cantidad); 
    while ((leidos = getline(&linea,&capacidad,f_archivo)) > 0) {
        reemplazar_caracter_corte(linea,SALTO_DE_LINEA);
        char **strv=split(linea,',');
        if (!strv) {
        	free(linea);
        	return NULL;
        } 
        size_t id=atoi(strv[0]);
        double saldo=atof(strv[1]);
        char* coordenadas=strv[2];  
        usuario_t* usuario=crear_usuario(id,saldo,coordenadas);
        if (!usuario) {
        	free_strv(strv);
        	free(linea);
        	return NULL;
        }
        vector_guardar(vector,indice,usuario);
        indice++;
        free_strv(strv);
    }
    free(linea);
    return vector; 
}

usuario_t* crear_usuario(size_t id, double saldo, char* coordenadas) {
	usuario_t* usuario=malloc(sizeof(usuario_t));
	if (!usuario) return NULL;
	usuario->id=id;
	usuario->saldo=saldo;
	usuario->coordenadas=strdup(coordenadas);
	if (!usuario->coordenadas) {
		free(usuario);
		return NULL;
	}
	return usuario;
}

void destruir_usuario(usuario_t* usuario) {
	free(usuario->coordenadas);
	free(usuario);
}

void destruir_usuario_wrapper(void* elem) {
    destruir_usuario((usuario_t*)elem);
}
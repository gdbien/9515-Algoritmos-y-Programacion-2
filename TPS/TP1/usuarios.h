#ifndef USUARIOS_H
#define USUARIOS_H
#include <stdlib.h>
#include <stdio.h>
#include "vector_dinamico.h"

typedef struct usuario {
	size_t id;
    double saldo;
    char* coordenadas;
} usuario_t;

usuario_t* crear_usuario(size_t id, double saldo, char* coordenadas);

vector_t* crear_vd_usuarios(size_t cantidad, FILE* f_archivo);

void destruir_usuario(usuario_t* usuario);

void destruir_usuario_wrapper(void* elem);

#endif
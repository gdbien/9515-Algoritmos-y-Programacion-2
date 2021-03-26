#ifndef PAGO_H
#define PAGO_H
#include "cola.h"
#include "vector_dinamico.h"

typedef struct pago {
	size_t id;
	double monto;
	char* codigo;
} pago_t;

pago_t* pago_crear(size_t id, double monto, char* codigo);

void agregar_pago(pago_t* pago,cola_t* cola);

bool procesar_pago(pago_t* pago,vector_t* vector);

void destruir_pago(pago_t* pago);

void destruir_pago_wrapper(void* elem);

#endif
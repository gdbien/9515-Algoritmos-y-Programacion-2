#ifndef CODIGOPAGO_H
#define CODIGOPAGO_H
#include "pila.h"
#include "vector_dinamico.h"

bool validar_usuario(pila_t* pila, vector_t* vector);

bool validar_pago(pila_t* pila, vector_t* vector);

bool pagar(pila_t* pila, vector_t* vector);

#endif
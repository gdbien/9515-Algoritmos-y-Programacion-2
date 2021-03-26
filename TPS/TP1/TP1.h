#ifndef TP1_H
#define TP1_H
#include "pago.h"
#include "usuarios.h"

double calcular_monto_cola(cola_t* cola);

bool guardar_cuentas(const char* file_name,vector_t* vector);

#endif
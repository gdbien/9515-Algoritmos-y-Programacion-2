#define _GNU_SOURCE 1
#include <string.h>
#include "pago.h"
#include "codigo_pago.h"
#include "strutil.h"
#include "funciones_aux.h"

#define VALIDAR_PAGO "validar_pago"
#define VALIDAR_USUARIO "validar_usuario"
#define PAGAR "pagar"

bool es_operacion(char* string) {
	if (son_iguales(string,VALIDAR_PAGO)) return true;
	if (son_iguales(string,VALIDAR_USUARIO)) return true;
	if (son_iguales(string,PAGAR)) return true;
	return false;
}

pago_t* pago_crear(size_t id, double monto, char* codigo) {
	pago_t* pago=malloc(sizeof(pago_t));
	if (!pago) return NULL;
	pago->id=id;
	pago->monto=monto;
	pago->codigo=strdup(codigo);
	if (!pago->codigo) {
		free(pago);
		return NULL;
	}
	return pago;
}

void destruir_pago(pago_t* pago) {
	free(pago->codigo);
	free(pago);
}

void destruir_pago_wrapper(void* elem) {
    destruir_pago((pago_t*)elem);
}

void agregar_pago(pago_t* pago, cola_t* cola) {
	cola_encolar(cola,pago);
}

bool procesar_pago(pago_t* pago, vector_t* vector) {
	pila_t* pila=pila_crear();
	if (!pila) return false;
	char **strv=split(pago->codigo,';');
	size_t i=0;
	bool hay_error=false;
	while (!hay_error && strv[i]!=NULL) {
		if (!es_operacion(strv[i])) {
			pila_apilar(pila,strv[i]);
		} else {
			if (son_iguales(strv[i],VALIDAR_USUARIO)) {
				if (!validar_usuario(pila,vector)) hay_error=true;				
			}
			if (son_iguales(strv[i],VALIDAR_PAGO)) {
				if (!validar_pago(pila,vector)) hay_error=true;
			}
			if (son_iguales(strv[i],PAGAR)) {
				if (!pagar(pila,vector)) hay_error=true;
			}
		}
		i++;	
	}
	free_strv(strv);
	pila_destruir(pila);
	return !hay_error;
}

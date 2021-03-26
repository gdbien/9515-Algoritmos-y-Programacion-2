#include "codigo_pago.h"
#include "funciones_aux.h"
#include "usuarios.h"

bool validar_usuario(pila_t* pila, vector_t* vector) {
	char* coordenadas=pila_desapilar(pila);
	size_t id;
	if (!es_sizet_valido(pila_desapilar(pila),&id)) return false;
	usuario_t* usuario=vector_obtener(vector,id);
	if (!usuario) return false;
	return son_iguales(coordenadas,usuario->coordenadas);
}

bool validar_pago(pila_t* pila, vector_t* vector) {
	double monto;
	if (!es_double_valido(pila_desapilar(pila),&monto)) return false;
	if (monto<0) return false;
	size_t id;
	if (!es_sizet_valido(pila_desapilar(pila),&id)) return false;
	usuario_t* usuario=vector_obtener(vector,id);
	if (!usuario) return false;
	return usuario->saldo>=monto;
}

bool pagar(pila_t* pila, vector_t* vector) {
	size_t id_emisor;
	if (!es_sizet_valido(pila_desapilar(pila),&id_emisor)) return false;
	size_t id_receptor;
	if (!es_sizet_valido(pila_desapilar(pila),&id_receptor)) return false;
	double monto;
	if (!es_double_valido(pila_desapilar(pila),&monto)) return false;
	if (monto<0) return false;
	usuario_t* usuario_emisor=vector_obtener(vector,id_emisor);
	if (!usuario_emisor) return false;
	usuario_t* usuario_receptor=vector_obtener(vector,id_receptor);
	if (!usuario_receptor) return false;
	((usuario_t*)vector->datos[id_receptor])->saldo+=monto;
	((usuario_t*)vector->datos[id_emisor])->saldo-=monto;
	return true;
}


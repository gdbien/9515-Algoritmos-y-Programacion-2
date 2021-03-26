#include "TP1.h"

double calcular_monto_cola(cola_t* cola) {
	double monto_total=0;
	for (size_t i=0;i<cola_ver_tamanio(cola);i++) {
		pago_t* pago=cola_desencolar(cola);
		monto_total+=pago->monto;
		cola_encolar(cola,pago);
	}
	return monto_total;
}

bool guardar_cuentas(const char* file_name,vector_t* vector) {
	FILE* f_archivo=fopen(file_name,"w");
	if (!f_archivo) return false;
	size_t i=0;
	while (i<vector_obtener_tamanio(vector)) {
		usuario_t* usuario=vector_obtener(vector,i);
		fprintf(f_archivo,"%zu,%.2lf,%s\n",usuario->id,usuario->saldo,usuario->coordenadas);
		i++;
	}
	fclose(f_archivo);
	return true;
}
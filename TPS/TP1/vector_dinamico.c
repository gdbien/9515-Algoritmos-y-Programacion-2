#include "vector_dinamico.h"

// Funciones del alumno.


bool es_pos_valida(size_t rango, size_t posicion) {
   return posicion<rango;
}

void vector_destruir(vector_t* vector, void destruir_dato(void *)) {
    if(destruir_dato) {
        for (size_t i=0;i<vector->tam;i++) {
            destruir_dato(vector->datos[i]);
        }  
    }
    free(vector->datos);
    free(vector);
}

void* vector_obtener(vector_t* vector, size_t pos) {
    return es_pos_valida(vector->tam,pos) ? vector->datos[pos] : NULL;
}

bool vector_guardar(vector_t* vector, size_t pos, void* valor) {
    if (es_pos_valida(vector->tam,pos)) {
        vector->datos[pos]=valor;
        return true;
    }
    return false;
}

size_t vector_obtener_tamanio(vector_t* vector) {
    return vector->tam;
}

vector_t* vector_crear(size_t tam) {
    vector_t* vector=malloc(sizeof(vector_t));
    if (!vector) return NULL;
    vector->datos=malloc(tam *sizeof(void*));
    if (tam > 0 && vector->datos == NULL) {
        free(vector);
        return NULL;
    }
    vector->tam=tam;
    return vector;
}


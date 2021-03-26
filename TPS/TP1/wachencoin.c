#define _POSIX_C_SOURCE 200809L //getline
#include "TP1.h"
#include "strutil.h"
#include "funciones_aux.h"
//              Comandos
#define AGREGAR_PAGO "agregar_pago" 
#define PAGOS_PENDIENTES "pagos_pendientes" 
#define PROCESAR "procesar"
#define GUARDAR_CUENTAS "guardar_cuentas"
#define FINALIZAR "finalizar"
//
#define SALTO_DE_LINEA '\n'

bool es_comando_valido(char* string) {
    if(son_iguales(string,AGREGAR_PAGO)) return true;
    if(son_iguales(string,PAGOS_PENDIENTES)) return true;
    if(son_iguales(string,PROCESAR)) return true;
    if(son_iguales(string,GUARDAR_CUENTAS)) return true;
    if(son_iguales(string,FINALIZAR)) return true;
    return false;
}

int main(int argc,char* argv[]) {
    if (argc != 2) {
        fprintf(stderr,"Error en comando %s\n",argv[0]);
        return 0;
    }

    const char* file_name = argv[1];   
    size_t cantidad_usuarios=obtener_cantidad_lineas(file_name);
    FILE* f_archivo=fopen(file_name,"r");
    if (!f_archivo){
        fprintf(stderr,"No se encontro el archivo de cuentas");
        return 0;
    }
    vector_t* vector=crear_vd_usuarios(cantidad_usuarios,f_archivo);
    cola_t* cola_procesos=cola_crear();
    bool terminar=false;
    char* linea = NULL; size_t capacidad = 0; ssize_t leidos;
    
    while (!terminar && (leidos = getline(&linea,&capacidad,stdin)) > 0) {
        reemplazar_caracter_corte(linea,SALTO_DE_LINEA);
        char **strv=split(linea,' ');
        if (!es_comando_valido(strv[0])) {
            fprintf(stderr,"Error en comando %s\n",strv[0]);
            terminar=true;
        }        
        if (son_iguales(strv[0],FINALIZAR)) {
            if (strv[1]!=NULL) {
                fprintf(stderr,"Error en comando %s\n",strv[0]);
            } else {
                fprintf(stdout,"OK\n");  
            }
            terminar=true;
        }
        if (son_iguales(strv[0],PAGOS_PENDIENTES)) {
            if (strv[1]!=NULL) {
                fprintf(stderr,"Error en comando %s\n",strv[0]);
                terminar=true;
            } else {
                fprintf(stdout,"%zu,%.2lf\n",cola_ver_tamanio(cola_procesos),calcular_monto_cola(cola_procesos)); 
                fprintf(stdout,"OK\n");  
            } 
        }
        if (son_iguales(strv[0],PROCESAR)) {
            size_t cantidad_procesar;
            if (strv[1]==NULL || strv[2]!=NULL || !es_sizet_valido(strv[1],&cantidad_procesar)) { //Chequear luego
                fprintf(stderr,"Error en comando %s\n",strv[0]);
                terminar=true;
            } else {   
                size_t cantidad_total_pagos=cola_ver_tamanio(cola_procesos);                                   
                size_t i=0;                     
                while (i<cantidad_procesar && i<cantidad_total_pagos) {
                    pago_t* pago=cola_desencolar(cola_procesos);
                    if (!procesar_pago(pago,vector)) {
                        fprintf(stderr,"Error en pago %zu\n",pago->id);
                    } 
                    destruir_pago(pago);
                    i++;  
                }
                fprintf(stdout,"OK\n"); 
            } 
        }
        if (son_iguales(strv[0],GUARDAR_CUENTAS)) {
            if (strv[1]==NULL || strv[2]!=NULL || !guardar_cuentas(strv[1],vector)) {
                fprintf(stderr,"Error en comando %s\n",strv[0]);
                terminar=true;
            } else {
                fprintf(stdout,"OK\n");   
            }  
        }
        if (son_iguales(strv[0],AGREGAR_PAGO)) {
            if (strv[1]==NULL ||strv[2]==NULL || strv[3]==NULL || strv[4]!=NULL) {
                fprintf(stderr,"Error en comando %s\n",strv[0]);
                terminar=true;
            } else {
                size_t id;
                es_sizet_valido(strv[1],&id);
                double monto;
                es_double_valido(strv[2],&monto);
                pago_t* pago=pago_crear(id,monto,strv[3]);
                if (!pago) {
                    terminar=true;
                } else {
                    agregar_pago(pago,cola_procesos);
                    fprintf(stdout,"OK\n"); 
                }    
            }
        } 
    free_strv(strv);      
    }
    vector_destruir(vector,&destruir_usuario_wrapper);
    cola_destruir(cola_procesos,&destruir_pago_wrapper);
    fclose(f_archivo);
    free(linea);
    return 0;
}



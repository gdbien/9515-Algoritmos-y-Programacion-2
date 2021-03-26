#!/usr/bin/env python3

import sys
from seis_grados import *

CAMINO_KB = "camino_hasta_KB"
BACON_NUMBER = "bacon_number"
BN_MAYOR_A_6 = "bacon_number_mayor_a_6"
BN_INFINITO = "bacon_number_infinito"
BN_PROMEDIO = "KBN_promedio"
SIMILARES_KB = "similares_a_KB"
POPULARIDAD_CONTRA_KB = "popularidad_contra_KB"
CANT_PELICULAS = "cantidad_peliculas"
CANT_ACTORES = "cantidad_actores"
FINALIZAR = "q"

KB = "Bacon Kevin"
GRADOS_DE_SEPARACION = 6
INFINITO = -1

def main():
    if(len(sys.argv) < 2):
        sys.exit("Se necesita que se pase el archivo con el database.")
    database = grafo_crear(sys.argv[1])

    inp = input("Ingrese comando ('q' para finalizar): ")
    entrada = inp.split(None, 1);
    cant_parametros = len(entrada)
    if cant_parametros == 2:
        parametro = entrada[1].replace("'","")
    comando = entrada[0]
    while comando != FINALIZAR:
        if comando == CAMINO_KB:
            if cant_parametros != 2:
                sys.exit("Faltan parámetros. Llamado: camino_hasta_KB <actor>")
            path = camino(database, KB, parametro)
            if path == False:
                print("El actor ingresado no existe :P")
            elif path == NO_HAY_CAMINO:
                print("No hay camino posible.")
            else:
                for elemento in path:
                    print(elemento[0], "actuó con", elemento[1], "en", elemento[2], ".")
        elif comando == BACON_NUMBER:
            if cant_parametros != 2:
                sys.exit("Faltan parámetros. Llamado: bacon_number <actor>")
            bacon_number = actor_number(database, KB, parametro)
            if bacon_number == False:
                print("El actor ingresado no existe.")
            else:
                print("'",parametro,"' tiene un Kevin Bacon number igual a", bacon_number, ".")
        elif comando == BN_MAYOR_A_6:
            numbers = actor_number_desde(database, KB, GRADOS_DE_SEPARACION)
            print("Los actores con un KBN mayor a 6 son:")
            for bacon_number in numbers.keys():
                print("Con KBN igual a", bacon_number, ":", len(numbers[bacon_number]), "actores.")
        elif comando == BN_INFINITO:
            numbers = actor_number_desde(database, KB, INFINITO)
            print("Los actores con un Bacon Number infinito son", len(numbers))
        elif comando == BN_PROMEDIO:
            numbers = actor_number_desde(database, KB, 1)
            print("El Kevin Bacon Number promedio es", calcular_promedio_actor(numbers))
        elif comando == SIMILARES_KB:
            if cant_parametros != 2:
                print("Faltan parámetros. Llamado: similares_a_KB <cantidad>")
            else:
                print("Los", parametro, "más similares a KB son", similares(database, KB, int(parametro)))
        elif comando == POPULARIDAD_CONTRA_KB:
            if cant_parametros != 2:
                sys.exit("Faltan parámetros. Llamado: popularidad_contra_KB < actor>")
            popular = popularidad(database,parametro)
            if popular == False:
                print("El actor ingresado no existe.")
            else:
                porcentaje_popularidad = popular*100/popularidad(database,KB)
                print(parametro, "es un", porcentaje_popularidad, "de lo popular que es Kevin Bacon.")
        elif comando == CANT_PELICULAS:
            print("El database contiene", cantidad_peliculas(database), " peliculas.")
        elif comando == CANT_ACTORES:
            print("El database contiene", cantidad_actores(database), "actores.")
        else:
            print("El comando ingresado no es válido.")

        inp = input("Ingrese comando ('Q' para finalizar): ")
        entrada = inp.split(None, 1);
        cant_parametros = len(entrada)
        if cant_parametros == 2:
            parametro = entrada[1].replace("'","")
        comando = entrada[0]

main()

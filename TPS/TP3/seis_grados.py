#!/usr/bin/env python3

from grafo import *
from collections import deque
from collections import Counter
from random import randint
import heapq

SEPARADOR_LINEA = ','
INFINIT0 = -1
NO_HAY_CAMINO = -1

def grafo_crear(nombre_archivo):
    """
    Crea un grafo de conexiones de actores a partir de un archivo de datos.

    PRE: Recibe el nombre de un archivo separado por comas que contenga de lineas:
        actor,pelicula,pelicula,pelicula
        que equivalen a: vertice,arista,arista,arista
    POST: Devuelve un grafo creado a partir de estos datos.
    """
    diccio_pelis = {}
    grafo = graph()
    with open(nombre_archivo, "r") as database:
        for line in database:
            linea = line.split(SEPARADOR_LINEA)
            linea[len(linea)-1] = linea[len(linea)-1].replace("\n","")
            grafo.agregar_vertice(linea[0])
            grafo.agregar_arista(linea[0], linea[0], len(linea)-1)
            for i in range(1,len(linea)):
                if linea[i] not in diccio_pelis:
                    diccio_pelis[linea[i]] = []
                for actor in diccio_pelis[linea[i]]:
                    grafo.agregar_arista(linea[0], actor,linea[i])
                diccio_pelis[linea[i]].append(linea[0])
    return grafo

def camino(grafo, origen, llegada):
    """
    Devuelve el camino entre un actor de origen y uno de llegada.

    PRE: Recibe el grafo, un actor de origen y un actor de llegada.
    POST: Devuelve una lista ordenada de cadenas (películas) para llegar desde
        el origen hasta el final.
    """
    camino = []
    if not origen in grafo.obtener_vertices(): return False
    if not llegada in grafo.obtener_vertices(): return False
    padre,orden = bfs(grafo, origen)
    if not llegada in padre: return NO_HAY_CAMINO
    actual = llegada
    while padre[actual] != None:
        padre_actual = padre[actual]
        info_peliculas = grafo.obtener_arista(actual, padre_actual)
        tupla_camino = (padre_actual, actual, info_peliculas[0])
        camino.append(tupla_camino)
        actual = padre_actual
    return camino[::-1]


def actores_a_distancia(grafo, origen, n):
    """
    Devuelve los actores a distancia n del recibido.

    PRE: Recibe el grafo, el actor de origen y el número deseado.
    POST: Devuelve la lista de cadenas (actores) a n pasos del recibido.
    """
    if not origen in grafo.obtener_vertices(): return False
    if n == 0: return [origen]
    visitados = {}
    orden = {}
    padre = {}
    lista_actores_n = []
    padre[origen] = None
    orden[origen] = 0
    q = deque()
    q.append(origen)
    visitados[origen] = True
    while len(q) > 0:
        v = q.popleft()
        for w in grafo.obtener_adyacentes(v):
            if w not in visitados:
                visitados[w] = True
                padre[w] = v
                orden[w] = orden[v] + 1
                if orden[w] == n:
                    lista_actores_n.append(w)
                elif orden[w] > n:
                    break
                q.append(w)
    return sorted(lista_actores_n)

def popularidad(grafo, actor):
    """
    Calcula la popularidad del actor recibido.

    PRE: Recibe el grafo y un actor de origen
    POST: Devuelve un entero que simboliza la popularidad: todos los adyacentes
        de los adyacentes del actor, multiplicado por su cantidad de peliculas
    """
    if not actor in grafo.obtener_vertices(): return False
    act_dist_2 = actores_a_distancia(grafo, actor, 2)
    pelis_actuadas = grafo.obtener_arista(actor, actor)[0]
    return len(act_dist_2)*pelis_actuadas


def similares(grafo, origen, n):
    """
    Calcula los n actores más similares al actor de origen y los devuelve en una
    lista ordenada de mayor similitud a menor.

    PRE: Recibe el grafo, el actor de origen, y el n deseado
    POST: Devuelve una lista de los n actores no adyacentes más similares al
        pedido. La lista no debe contener al actor de origen.
    """
    if not origen in grafo.obtener_vertices(): return False
    actores = []
    for i in range(0, 1000):
        actual = origen
        for j in range(0, 2):
            adyacentes = grafo.obtener_adyacentes(actual)
            if len(adyacentes) == 0: continue
            movimiento = randint(0, len(adyacentes)-1)
            while adyacentes[movimiento] == origen:
                movimiento = randint(0, len(adyacentes)-1)
            actual = adyacentes[movimiento]
        actores.append(actual)
    contador = Counter(actores)
    mas_similares = []
    for elemento in contador.most_common(n):
        mas_similares.append(elemento[0])

    return mas_similares

def actor_number(database, actor1, actor2):
    """
    Devuelve el actor Number del actor ingresado.
    Pre: recibe el database y el actor.
    """
    if actor1 == actor2: return 0
    path = camino(database, actor1, actor2)
    if not path: return False
    if path == NO_HAY_CAMINO: return NO_HAY_CAMINO
    return len(path)

def actor_number_desde(database, actor, desde):
    """
    Devuelve un diccionario donde las claves son los actor_numbers que se
    encuentran en el rango pasado, y los datos asociados son listas de los
    actores con ese actor_number.
    """
    if not actor in database.obtener_vertices(): return False
    diccio_numbers = {}
    number = desde
    actores_dist = actores_a_distancia(database, actor, number)
    while len(actores_dist) != 0:
        diccio_numbers[number] = actores_dist
        number += 1
        actores_dist = actores_a_distancia(database, actor, number)

    return diccio_numbers

def actor_number_igual(database, actor, igual):
    if not actor in database.obtener_vertices(): return False
    numbers = set()
    for vertice in database.obtener_vertices():
        number = actor_number(database, actor, vertice)
        if number == igual:
            number.add(vertice)
    return list(numbers)

def calcular_promedio_actor(diccionario):
    return (sum(diccionario.keys()))/len(diccionario)

def cantidad_peliculas(database):
    """
    Devuelve la cantidad de peliculas del database.
    Pre: recibe el grafo.
    """
    total = 0
    for vertice in database.obtener_vertices():
        total += database.obtener_arista(vertice, vertice)[0]
    return total

def cantidad_actores(database):
    """
    Devuelve la cantidad de actores del database.
    Pre: recibe el grafo.
    """
    return len(database.obtener_vertices())

def bfs(grafo,origen):
    visitados = {} #diccionario
    padre = {}
    orden = {}
    padre[origen] = None
    orden[origen] = 0
    visitados[origen] = True
    bfs_visitar(grafo, origen, visitados, padre, orden)
    return padre, orden

def bfs_visitar(grafo, origen, visitados, padre, orden):
    q = deque()
    q.append(origen)
    while len(q) > 0:
        v = q.popleft()
        for w in grafo.obtener_adyacentes(v):
            if w not in visitados:
                visitados[w] = True
                padre[w] = v
                orden[w] = orden[v] + 1
                q.append(w)

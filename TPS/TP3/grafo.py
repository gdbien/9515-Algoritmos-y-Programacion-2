#!/usr/bin/env python3

class edge(object):
    """docstring for edge"""
    def __init__(self, info, peso=1):
        self.peso = peso
        self.info = [info]

    def obtener_peso(self):
        return self.peso

    def obtener_info(self):
        return self.info

class graph(object):
    """ The graphnut nut is a giant nut! """
    def __init__(self, pesado=False):
        self.pesado = pesado
        self.cant_vertices = 0
        self.diccio = {}

    def son_adyacentes(self, vertice1, vertice2):
        return vertice2 in self.diccio[vertice1]

    def agregar_arista(self, vertice1, vertice2, info, peso=1):
        if not self.son_adyacentes(vertice1, vertice2):
            self.diccio[vertice1][vertice2] = edge(info)
            self.diccio[vertice2][vertice1] = edge(info)
        else:
            self.diccio[vertice1][vertice2].obtener_info().append(info)
            self.diccio[vertice2][vertice1].obtener_info().append(info)

    def borrar_arista(self, vertice1, vertice2):
        self.diccio[vertice1].pop(vertice2)
        self.diccio[vertice2].pop(vertice1)

    def agregar_vertice(self, nombre_vertice):
        self.diccio[nombre_vertice] = {}
        self.cant_vertices += 1

    def obtener_arista(self, vertice1, vertice2):
        return list(self.diccio[vertice1][vertice2].obtener_info())

    def borrar_vertice(self, nombre_vertice):
        for vertice in self.diccio:
            if nombre_vertice in self.diccio[vertice]:
                self.diccio[vertice].pop(nombre_vertice)
        self.diccio.pop[nombre_vertice]

    def obtener_adyacentes(self, nombre_vertice):
        lista_adyacentes = []
        if nombre_vertice in self.obtener_vertices():
            lista_adyacentes = list(self.diccio[nombre_vertice].keys())
        return lista_adyacentes

    def obtener_aristas(self):
        info_aristas = set()
        for vertice1 in self.diccio:
            for vertice2 in self.diccio[vertice1]:
                info_aristas.update(self.diccio[vertice1][vertice2].obtener_info())
        return list(info_aristas)

    def obtener_vertices(self):
        return list(self.diccio.keys())

    def obtener_aristas_vertice(self,vertice):
        info_aristas = []
        for v in self.obtener_adyacentes(vertice):
            #arista = devolver_arista(vertice,v)
            #for elemento in arista.obtener_info():
            arista = self.obtener_arista(vertice,v)
            print(arista)
            for elemento in arista:
                if elemento not in info_aristas:
                    info_aristas.append(elemento)
        return info_aristas

#include "tp0.h"

#define LARGO_CERO -1
#define PRIMERO_MENOR -1
#define SEGUNDO_MENOR 1
#define IGUALES 0

/* ******************************************************************
 *                     FUNCIONES A COMPLETAR
 * *****************************************************************/

/* swap() intercambia dos valores enteros.
 */
void swap(int* x, int* y) {
	int aux=*x;
	*x=*y;
	*y=aux;
}

/* maximo() busca el mayor elemento del arreglo y devuelve su posicion.
 * Si el vector es de largo 0, devuelve -1.
 */
int maximo(int vector[], int n) {
	if (n==0) {
		return LARGO_CERO;
	}

	int posicionMax=0;

	for (int i=0;i<n;i++) {
		if (vector[posicionMax]<vector[i]) {
			posicionMax=i;
		}
	}
	return posicionMax;
}

/* La función comparar recibe dos vectores y sus respectivas longitudes
 * y devuelve -1 si el primer vector es menor que el segundo; 0 si son
 * iguales; y 1 si el segundo es menor.
 *
 * Un vector es menor a otro cuando al compararlos elemento a elemento,
 * el primer elemento en el que difieren no existe o es menor.
 */
int comparar(int vector1[], int n1, int vector2[], int n2) {
	int i=0;

	while (i<n1 && i<n2) {
		if (vector1[i]<vector2[i]) {
			return PRIMERO_MENOR;
		}
		if (vector1[i]>vector2[i]) {
			return SEGUNDO_MENOR;
		}
		i++;
	}
	if (n1<n2) {
		return PRIMERO_MENOR;
	} else {
		if (n1>n2) {
			return SEGUNDO_MENOR;
		}
		return IGUALES;
	}
}

/* selection_sort() ordena el arreglo recibido mediante el algoritmo de
 * selección.
 */
void seleccion(int vector[], int n) {
	int posicionMax;
	
	while (n>0) {
		posicionMax=maximo(vector,n);
		swap(&vector[posicionMax],&vector[n-1]);
		n--;
	}
}

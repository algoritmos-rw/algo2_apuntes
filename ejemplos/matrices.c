#include <stdio.h>
#include <stdlib.h>

/* funciona bien pero es feo */
void imprimir_matriz1(int v[][4], int filas) {
	for (int i=0; i < filas; i++) {
		for (int j=0; j < 4; j++) {
			printf("%d ", v[i][j]);
		}
		printf("\n");
	}
}

/* Funciona pero se queja de parametros invalidos */
void imprimir_matriz2(void *aux, size_t filas, size_t cols) {
	int *v = aux;
	for (int i=0; i < filas; i++) {
		for (int j=0; j < cols; j++) {
			printf("%d ", *(v+(i*cols)+j));
		}
		printf("\n");
	}
}

void imprimir_matriz3(int* v, size_t filas, size_t cols) {
	for (int i=0; i < filas; i++) {
        int *fila = v+i*cols;
		for (int j=0; j < cols; j++) {
			printf("%d ", fila[j]);
		}
		printf("\n");
	}
}

void imprimir_matriz4(int** v, size_t filas, size_t cols) {
	for (int i=0; i < filas; i++) {
		for (int j=0; j < cols; j++) {
			printf("%d ", v[i][j]);
		}
		printf("\n");
	}
}

int main(void) {

	int filas = 3; 
	int cols = 4;

	int v[][4] = { { 1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
	imprimir_matriz1(v, filas);
	imprimir_matriz2(v, filas, cols);
	imprimir_matriz3(v, filas, cols);

	int *w[filas];
	for (int i=0; i < filas; i++) {
		w[i] = malloc(cols*sizeof(int));
		for (int j=0; j < cols; j++) {
			w[i][j] = i*10+j;
		}	
		printf("w[%d]: %p\n", i, w[i]);
	}
	imprimir_matriz4(w, filas, cols);


	return 0;
}

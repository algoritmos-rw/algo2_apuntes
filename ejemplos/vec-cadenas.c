#include <stdio.h>
#include <stdlib.h>

void imprimir_cadenas(char *palabras[], int cant) {
	for (int i=0; i < cant; i++) {
		printf("%s\n", palabras[i]);
	}
}


int main(void) {

	char* palabras[] = {"Hola", "que", "tal"};
	imprimir_cadenas(palabras, 3);
	return 0;
}

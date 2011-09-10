#include <stdio.h>
#include <stdlib.h>

void imprimir_cadenas(char *palabras[], int cant) {
	for (int i=0; i < cant; i++) {
		printf("%p %s\n", palabras[i], palabras[i]);
	}
}

int b = 5;

int main(int argc, char* argv[]) {

	printf("argv: %p\n", argv);
	imprimir_cadenas(argv, argc);

	char *palabras[] = {"uno", "dos", "tres"};
	printf("palabras: %p\n", palabras);
	imprimir_cadenas(palabras, 3);

	printf("b: %p %d\n", &b, b);

	int c = 8;
	printf("c: %p %d\n", &c, c);

	char* hola = malloc(10);
	printf("hola: %p\n", hola);

	return 0;
}

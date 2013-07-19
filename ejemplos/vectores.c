#include <stdio.h>

void f(int b) {
	int a[] = {1,2,3,4,5};
	int *p = a;

	printf ("b %p\n", (void *) &b);
	printf ("a %p\n", (void *) a);
	printf ("p %p\n", (void *) p);
	printf ("&p %p\n", (void *) &p);

}

int main(void) {

	f(1);
	return 0;
}

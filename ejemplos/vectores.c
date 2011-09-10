#include <stdio.h>

void f(int b) {
	int a[] = {1,2,3,4,5};
	int *p = a;

	printf ("b %p\n", &b);
	printf ("a %p\n", a);
	printf ("p %p\n", p);
	printf ("&p %p\n", &p);

}

int main(void) {

	f(1);
	return 0;
}

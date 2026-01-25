#include <stdio.h>

void add_to(int * a, int b) {
	*a = *a + b;
}

int main(){
	int x = 1;
	int const c = 3;

	x = c;
	/* c = 7;
	*/

	add_to(&x, 7);
	add_to(&c, 7);

	printf("x=%d c=%d\n", x, c);

	return 0;
}

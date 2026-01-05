#include <stdio.h>

int main() {
	int w = 1337;
	int x = 255;
	int y = 511;
	int z = 1023;
	while(w--) {
		y = x + w;
		printf("ayo\n");
	}
	z = y * x;

	return 0;
}

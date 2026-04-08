#include <stdio.h>

int main(int argc, char *argv[]) {

	printf("%d XOR %d = %d\n", false,false, false^false);
	printf("%d XOR %d = %d\n", true,false, true^false);
	printf("%d XOR %d = %d\n", false,true, false^true);
	printf("%d XOR %d = %d\n", true,true, true^true);
}


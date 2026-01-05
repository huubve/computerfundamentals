#include <stdio.h>

int main( int argc, char * argv[]) {

	size_t argi = 1;
	while ( argv[argi] ) {
		printf("%s", argv[argi]);
		if ( argv[argi+1] )
			printf(" ");
		argi++;
	}
	printf("\n");
	return 0;
}

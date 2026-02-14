#include <stdio.h>

int	main( int argc, char *argv[argc+1]){
	short	x[3];

	x[0] = 31;
	x[1] = 24;
	x[2] = 7;

	printf("%hd %hd %hd\n", x[0], x[1], x[2]);

	printf("x=    %lx\n&x=   %lx\n&x[0]=%lx\n&x[1]=%lx\n&x[2]=%lx\n",
		(unsigned long)x,
		(unsigned long)&x,
		(unsigned long)&(x[0]),
		(unsigned long)&(x[1]),
		(unsigned long)&(x[2])
	);

	return 0;
}

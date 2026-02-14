#include <stdlib.h>
#include <stdio.h>

#define STACK_SIZE 10

int	main(int argc, char *argv[argc+1]) {

	int	stack[STACK_SIZE];
	int *	const stack_highest = stack + STACK_SIZE - 1;
	int *	top = stack - 1;

	for (int argi = 1; argi < argc; argi++) {
		switch ( *argv[argi] ) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			if (top == stack_highest) {
				fprintf(stderr, "%s: error at argument %d ('%s'): stack overflow.\n", argv[0], argi, argv[argi]);
				exit(1);
			}
			*++top = atoi(argv[argi]);
			break;
		case 'p':
			if (top < stack) {
				fprintf(stderr, "%s: error at argument %d ('%s'): stack underflow.\n", argv[0], argi, argv[argi]);
				exit(1);
			}
			printf("%d ", *top);
			break;
		case '+':
		case '-':
		case 'x':
			if (top < stack + 1) {
				fprintf(stderr, "%s: error at argument %d ('%s'): stack underflow.\n", argv[0], argi, argv[argi]);
				exit(1);
			}
			switch ( *argv[argi] ) {
			case '+':
				*(top-1) += *top;
				break;
			case '-':
				*(top-1) -= *top;
				break;
			case 'x':
				*(top-1) *= *top;
				break;
			}
			top--;
			break;
		default:
			fprintf(stderr, "%s: error at argument %d ('%s'): unknown symbol.\n", argv[0], argi, argv[argi]);
			exit(2);
			break;
		}
	}
	printf("\n");
	return 0;
}

#include <stdlib.h>
#include <stdio.h>

/*
#define BIT(x,n) ((unsigned long)(((x)>>(n)&(unsigned long)1ul))
*/

int	sprintBits( unsigned char * bufp, void * object, int nbits, char spaces ) {

	unsigned long		objectBits;
	unsigned long const	numberOne = 1;
	char const		asciiZero = '0';

	if ( nbits < 1 || nbits > 8*sizeof(long long) || bufp == (unsigned char *)0 || object == (void *)0 ) {
		return 0;
	}

	objectBits = *(unsigned long long *)object;
	if ( spaces ) {
		bufp += nbits + nbits/spaces;
		if ( nbits % spaces == 0 ) {
			bufp--;
		}
	} else {
		bufp += nbits;
	}
	*bufp = (unsigned char)0;
	for ( unsigned short x = 1; nbits > 0; nbits--, x++) {
		*(--bufp) = asciiZero + ( objectBits & numberOne );
		if ( spaces && ((x % spaces) == 0)  ) {
			*(--bufp) = ' ';
		}
		objectBits >>= 1;
	}
	return 1;
}

int main(int argc, char *argv[argc+1]) {
	union {
		unsigned char c[4];
		int  i;
		unsigned int u;
		float f;
		unsigned long l;
	} x;
	unsigned char	bufje[2*8*sizeof(long long)+1];
	unsigned int	sum;

	printf("### unsigned int : 0 (+1) 9 ###\n"); fflush(stdout);
	for (x.u = 0; x.u < 10; x.u++) {
		sprintBits(bufje, &(x.u), 8*sizeof(int), 8);
		printf("%6u %s\n",x.u, bufje);  fflush(stdout);
	}

	printf("### unsigned int : 1 (*2) 2000.000.000 ###\n"); fflush(stdout);
	sum = 0;
	for (x.u = 1; x.u < 2000000000; x.u*=2) {
		sum += x.u;
		sprintBits(bufje, &(x.u), 8*sizeof(x.u), 8);
		printf("%10u %s\n",x.u, bufje); 
	}
	sprintBits(bufje, &(sum), 8*sizeof(x.u), 8);
	printf("%10u %s\n",sum, bufje); 
	sum++;
	sprintBits(bufje, &(sum), 8*sizeof(x.u), 8);
	printf("%10u %s\n",sum, bufje); 
	sum--;
	sum*=2;
	sprintBits(bufje, &(sum), 8*sizeof(x.u), 8);
	printf("%10u %s\n",sum, bufje); 
	sum++;
	sprintBits(bufje, &(sum), 8*sizeof(x.u), 8);
	printf("%10u %s\n",sum, bufje); 
	sum++;
	sprintBits(bufje, &(sum), 8*sizeof(x.u), 8);
	printf("%10u %s\n",sum, bufje); 

	printf("### float : 0 (+1) 9 ###\n");
	for (x.f = 0.0; x.f < 10.0; x.f += 1.0) {
		sprintBits(bufje, &(x.f), 8*sizeof(float), 8);
		printf("%15.1f %s\n",x.f, bufje); 
	}

	printf("### float : 1 (*2) 129 ###\n");
	for (x.f = 1.0; x.f < 129.0; x.f *= 2.0) {
		sprintBits(bufje, &(x.l), 8*sizeof(float), 8);
		printf("%15.1f %s\n",x.f, bufje); 
	}

	printf("### float : 1000 (*2) 129000 ###\n");
	for (x.f = 1000.0; x.f < 129000.0; x.f *= 2.0) {
		sprintBits(bufje, &(x.l), 8*sizeof(float), 8);
		printf("%15.1f %s\n",x.f, bufje); 
	}

	printf("### float : 10^9 (*2) 129*10^9 ###\n");
	for (x.f = 1000000000.0; x.f < 129000000000.0; x.f *= 2.0) {
		sprintBits(bufje, &(x.l), 8*sizeof(float), 8);
		printf("%15.1f %s\n",x.f, bufje); 
	}

	printf("### ASCII ###\n");
	for (unsigned char c = 48; c < 58; c++ ) {
		sprintBits(bufje, &c, 8, 3);
		printf("%s = '%c'\n", bufje, c);
	}

	unsigned char upCaseMask = ~((unsigned char)1<<5);
	for (unsigned char c = 97; c < 123; c++ ) {
		unsigned char upc = c & upCaseMask;
		sprintBits(bufje, &c, 8, 3);
		printf("%s = '%c' | ", bufje, c);
		sprintBits(bufje, &upc, 8, 3);
		printf("%s = '%c'\n", bufje, upc);
	}

	return 0;
}

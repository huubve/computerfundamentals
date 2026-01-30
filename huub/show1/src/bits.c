#include <stdlib.h>
#include <stdio.h>

/*
#define BIT(x,n) ((unsigned long)(((x)>>(n)&(unsigned long)1ul))
*/

/*
	objectBits = *(unsigned long long *)object;
	if ( spaces ) {
		bufp += nbits + nbits/spaces;
		if ( nbits % spaces == 0 ) {
			bufp--;
		}
	} else {
		bufp += nbits;
	}
	*bufp = (char)0;
	for ( unsigned short x = 1; nbits > 0; nbits--, x++) {
		*(--bufp) = asciiZero + ( objectBits & numberOne );
		if ( spaces && ((x % spaces) == 0)  ) {
			*(--bufp) = ' ';
			*/
      
int	sprintBits( char * bufp, void * object, int nbits) {

	unsigned long		objectCopy;
	unsigned long const	numberOne = 1;
	char const		asciiZero = '0';

	if ( nbits < 1 || nbits > 8*sizeof(long long) || bufp == 0 || object == 0 ) {
		return 0;
	}

	objectCopy = *(unsigned long long *)object;

	/* correct and uses minimal extra variables on the stack
	 * by using the function formal parameters
	 * Drawback: you can't remember the size soyou can't return it.
	bufp += nbits;
	*bufp-- = (char)0;
	while ( nbits-- > 0 ) {
		*(bufp--) = asciiZero + ( objectCopy & numberOne );
		objectCopy >>= 1;
	}
	*/
	/* correct but error prone because you need to contruct the mental model
	 * of keeping the meaning of counter i in sync with
	 * the position of pointer p in the buffer
	char * p = bufp + nbits;
	*p-- = (char)0;
	for ( int i = nbits; i > 0; i-- ) {
		*(p--) = asciiZero + ( objectCopy & numberOne );
		objectCopy >>= 1;
	}
	*/

	char * p = bufp + nbits;
	*p-- = (char)0;
	while ( p >= bufp ) {
		*(p--) = asciiZero + ( objectCopy & numberOne );
		objectCopy >>= 1;
	}
	return nbits;
}

char *	reverse( char * s, int l) {
	char *	b = s;
	char *	e = s + l - 1;
	char	x;

	l /= 2;
	while ( l-- > 0 ) {
		x = *b;
		*b++ = *e;
		*e-- = x;
	}
	return s;
}
		
int main(int argc, char *argv[argc+1]) {
	union {
		char c[4];
		int  i;
		unsigned int u;
		float f;
		unsigned long l;
	} x;
	char	bufje[2*8*sizeof(long long)+1];
	unsigned int	sum;

	char	a0[] = "";
	char	a1[] = "X";
	char	a3[] = "abc";
	char	a4[] = "1234";

	printf("%s", a0); printf(" reversed = %s\n", reverse(a0, 0));
	printf("%s", a1); printf(" reversed = %s\n", reverse(a1, 1));
	printf("%s", a3); printf(" reversed = %s\n", reverse(a3, 3));
	printf("%s", a4); printf(" reversed = %s\n", reverse(a4, 4));

	x.c[0] = 126;
	sprintBits(bufje, &(x.c), 8);
	printf("%s\n", bufje);  fflush(stdout);

	printf("### unsigned int : 0 (+1) 9 ###\n"); fflush(stdout);
	for (x.u = 0; x.u < 10; x.u++) {
		sprintBits(bufje, &(x.u), 8*sizeof(int));
		printf("%6u %s\n",x.u, bufje);  fflush(stdout);
	}

	printf("### unsigned int : 1 (*2) 2000.000.000 ###\n"); fflush(stdout);
	sum = 0;
	for (x.u = 1; x.u < 2000000000; x.u*=2) {
		sum += x.u;
		sprintBits(bufje, &(x.u), 8*sizeof(x.u));
		printf("%10u %s\n",x.u, bufje); 
	}
	sprintBits(bufje, &(sum), 8*sizeof(x.u));
	printf("%10u %s\n",sum, bufje); 
	sum++;
	sprintBits(bufje, &(sum), 8*sizeof(x.u));
	printf("%10u %s\n",sum, bufje); 
	sum--;
	sum*=2;
	sprintBits(bufje, &(sum), 8*sizeof(x.u));
	printf("%10u %s\n",sum, bufje); 
	sum++;
	sprintBits(bufje, &(sum), 8*sizeof(x.u));
	printf("%10u %s\n",sum, bufje); 
	sum++;
	sprintBits(bufje, &(sum), 8*sizeof(x.u));
	printf("%10u %s\n",sum, bufje); 

	printf("### float : 0 (+1) 9 ###\n");
	for (x.f = 0.0; x.f < 10.0; x.f += 1.0) {
		sprintBits(bufje, &(x.f), 8*sizeof(float));
		printf("%15.1f %s\n",x.f, bufje); 
	}

	printf("### float : 1 (*2) 129 ###\n");
	for (x.f = 1.0; x.f < 129.0; x.f *= 2.0) {
		sprintBits(bufje, &(x.l), 8*sizeof(float));
		printf("%15.1f %s\n",x.f, bufje); 
	}

	printf("### float : 1000 (*2) 129000 ###\n");
	for (x.f = 1000.0; x.f < 129000.0; x.f *= 2.0) {
		sprintBits(bufje, &(x.l), 8*sizeof(float));
		printf("%15.1f %s\n",x.f, bufje); 
	}

	printf("### float : 10^9 (*2) 129*10^9 ###\n");
	for (x.f = 1000000000.0; x.f < 129000000000.0; x.f *= 2.0) {
		sprintBits(bufje, &(x.l), 8*sizeof(float));
		printf("%15.1f %s\n",x.f, bufje); 
	}

	printf("### ASCII ###\n");
	for (char c = 48; c < 58; c++ ) {
		sprintBits(bufje, &c, 8);
		printf("%s = '%c'\n", bufje, c);
	}

	char upCaseMask = ~((char)1<<5);
	for (char c = 97; c < 123; c++ ) {
		char upc = c & upCaseMask;
		sprintBits(bufje, &c, 8);
		printf("%s = '%c' | ", bufje, c);
		sprintBits(bufje, &upc, 8);
		printf("%s = '%c'\n", bufje, upc);
	}

	return 0;
}

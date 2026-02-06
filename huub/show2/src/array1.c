#include <stdio.h>

/* the old way of arranging SPOT about the size of your array was with a define */
#define MAX_X 13


int main(int argc, char *argv[argc+1]) {
	unsigned int	i;
	int		xs[MAX_X];
	printf("line: %3d\n", __LINE__);
	printf("------------------------------\n");
	printf(" i  64*i*i*i>>i\n");
	printf("------------------------------\n");
	i = 0;
	while ( i < MAX_X ) {
		/* why? Dunno. */
		/* the old way of arranging SPOT about the size of your array was with a define */
		xs[i] = (64 * i * i * i ) >> i;
		printf("%2d  %6d\n", i, xs[i]);
		i++;
	}
	printf("------------------------------\n\n\n");

	int		nrs[] = { 5, 7, 11, 13, 17, 21};
	/* the way to get the length of an array at compiletime is
	 * to get the size of the array in bytes and divide by the size of the elements in bytes
	 * so, if you change above initialization, nothing else needs to change
	 */
	int		i_squares[sizeof(nrs)/sizeof(nrs[0])];
	char		c_squares[sizeof(nrs)/sizeof(nrs[0])];
	unsigned char	uc_squares[sizeof(nrs)/sizeof(nrs[0])];

	int		n_nrs = sizeof(nrs)/sizeof(nrs[0]);


	i = 0;
	while ( i < n_nrs ) {
		i_squares[i] = nrs[i] * nrs[i];
		c_squares[i] = (char)nrs[i] * (char)nrs[i];
		uc_squares[i] = (unsigned char)nrs[i] * (unsigned char)nrs[i];
		i += 1;
	}


	printf("line: %3d\n", __LINE__);
	printf("------------------------------\n");
	printf("NUMBERS & SQUARES int---------\n");
	printf("------------------------------\n");
	printf("(int)  (int)\n");
	printf("   x    x*x\n");
	printf("------------------------------\n");
	i = 0;
	while ( i < n_nrs ) {
		printf(" %3d    %3d\n", nrs[i], i_squares[i]);
		i += 1;
	}
	printf("------------------------------\n");
	printf("-------- this seems ok -------\n");
	printf("------------------------------\n\n\n");



	printf("line: %3d\n", __LINE__);
	printf("------------------------------\n");
	printf("NUMBERS & SQUARES unsigned char\n");
	printf("------------------------------\n");
	printf("(int)   (uchar) (int)\n");
	printf("  x      x*x    (x*x)%%256 \n");
	printf("------------------------------\n");
	i = 0;
	while ( i < n_nrs ) {
		printf("%3d      %3d      %3d\n", nrs[i], uc_squares[i], i_squares[i]%256);
		i += 1;
	}
	printf("------------------------------\n");
	printf("can you explain overflow?\n");
	printf("------------------------------\n\n\n");



	printf("line: %3d\n", __LINE__);
	printf("------------------------------\n");
	printf("NUMBERS & SQUARES char -------\n");
	printf("------------------------------\n");
	printf("(int)   (char)  (int)\n");
	printf("  x      x*x     f(x) \n");
	printf("------------------------------\n");
	i = 0;
	while ( i < n_nrs ) {
		printf("%3d      %3d      %3d\n", nrs[i], c_squares[i], i_squares[i]%256<128 ? i_squares[i]%128: i_squares[i]%128-128);
		i += 1;
	}
	printf("------------------------------\n");
	printf("can you explain overflow?\n");
	printf("------------------------------\n\n\n");



 	/* in C, type char is nothing more and nothing less that an 8 bit int */
	char		name[] = { 67, 101, 103, 101, 107, 97 }; /* yes, small ints can be a char */
	int		n_name = sizeof(name)/sizeof(name[0]);

	printf("line: %3d\n", __LINE__);
	printf("------------------------------\n");
	printf("printing char with %%d versus %%c\n");
	printf("------------------------------\n");
	printf(" %%d      %%c\n");
	printf("------------------------------\n");
	i = 0;
	while ( i < n_name ) {
		printf("%3d      %c\n", name[i], name[i]);
		i += 1;
	}
	printf("------------------------------\n");
	printf("can you explain ASCII?\n");
	printf("------------------------------\n\n\n");



	printf("line: %3d\n", __LINE__);
	printf("------------------------------\n");
	printf("(unsigned)char are just small int's\n");
	printf("------------------------------\n");
	char a = 7, b = 9;
	printf("(char)%hhd + (char)%hhd = %hhd\n", a, b, (char)(a+b));
	a = 'F', b = 's';
	printf("%hhd(%c) + %hhd(%c) = %hhd\n", a, a, b, b, (char)(a+b));
	printf("------------------------------\n");
	printf("can you explain ASCII?\n");
	printf("------------------------------\n\n\n");


 	/* in C, type char is nothing more and nothing less that an 8 bit int */
	char		ascii_digits[]= { 48, 49,'2', '3', 52, 53, 54, '7', '8', '9' }; /* yes, char and small ints are interchangable */
	int		n_digits = sizeof(ascii_digits)/sizeof(ascii_digits[0]);
	
	printf("line: %3d\n", __LINE__);
	printf("------------------------------\n");
	printf("what you see is not what it is\n");
	printf("------------------------------\n");
	printf(" %%d      %%c\n");
	printf("------------------------------\n");
	i = 0;
	while ( i < n_digits ) {
		printf("%3d      %c\n", ascii_digits[i], ascii_digits[i]);
		i += 1;
	}
	printf("------------------------------\n");
	printf("can you explain ASCII?\n");
	printf("------------------------------\n\n\n");



	printf("line: %3d\n", __LINE__);
	printf("------------------------------\n");
	printf("with unsigned int, x<< is x*2\n");
	printf("------------------------------\n");
	printf(" i      1 << i\n");
	printf("------------------------------\n");
	i = 0;
	while ( i < 12 ) {
		printf("%3d   %6d\n", i, 1 << i);
		i += 1;
	}
	printf("------------------------------\n");
	printf("-------- this seems ok -------\n");
	printf("------------------------------\n\n\n");



	printf("line: %3d\n", __LINE__);
	printf("------------------------------\n");
	printf("with unsigned int, x<< is x*2\n");
	printf("------------------------------\n");
	printf(" i      5 << i\n");
	printf("------------------------------\n");
	i = 0;
	while ( i < 12 ) {
		printf("%3d   %6d\n", i, 5 << i);
		i += 1;
	}
	printf("------------------------------\n");
	printf("-------- this seems ok -------\n");
	printf("------------------------------\n\n\n");



	printf("line: %3d\n", __LINE__);
	printf("------------------------------\n");
	printf("with unsigned int, x<< is x*2\n");
	printf("------------------------------\n");
	printf(" i       << i\n");
	printf("------------------------------\n");
	i = 0;
	while ( i < 12 ) {
		printf("%3d   %6d\n", i, 30000000 << i);
		i += 1;
	}
	printf("------------------------------\n");
	printf("----until it isn't -----------\n");
	printf("------------------------------\n\n\n");



	printf("line: %3d\n", __LINE__);
	printf("------------------------------\n");
	printf("XOR is a magical operation\n");
	printf("------------------------------\n");
	long la = 13579113;
	long lb = 310197;
	printf("a=%10ld  b=%10ld\n", la, lb);
	printf("a = a^b\n");
	la ^= lb;
	printf("a=%10ld  b=%10ld\n", la, lb);
	printf("b = b^a\n");
	lb ^= la;
	printf("a=%10ld  b=%10ld\n", la, lb);
	printf("a = a^b\n");
	la ^= lb;
	printf("a=%10ld  b=%10ld\n", la, lb);
	printf("------------------------------\n\n\n");
	return 0;
}

	



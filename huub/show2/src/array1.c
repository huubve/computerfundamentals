#include <stdio.h>

#define THE_SIZE 6

int main(int argc, char *argv[argc+1]) {
	int	i;
	int	kwadraten[THE_SIZE];
	int	primes[] = { 1, 2, 3, 5, 7, 11};

	char	aap[] = {'c','h','i','m','p','a','n','s','e','e'};

	char	rund[] = "koe";

	i = 0;
	while ( i < THE_SIZE ) {
		kwadraten[i] = primes[i] * primes[i];
		i = i + 1;
	}
	i = 0;
	while ( i < THE_SIZE ) {
		printf("%03d ", kwadraten[i]);
		i = i + 1;
	}
	printf("\n");

	i = 0;
	while ( i < sizeof(aap) ) {
		printf("%c", aap[i]);
		i += 1;
	}
	printf("\n");
	i = 0;
	while ( i < sizeof(aap) ) {
		printf("%c", aap[i]);
		i += 1;
	}
	printf("\n");
	i = 0;
	while ( i < sizeof(rund) ) {
		printf("%c", rund[i]);
		i += 1;
	}
	printf("\n");

	return 0;
}

	



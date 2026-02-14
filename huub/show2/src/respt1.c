#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define MIN_BYTES	8UL
#define MAX_BYTES	((unsigned long)(1024UL*1024UL*256UL))
#define BUF_SIZE	(MAX_BYTES/sizeof(unsigned long))
#define RUN_BASE	MAX_BYTES
#define RUN_TUNING	(0.20)
#define CHAIN_LENGTH	100

unsigned long buf1[BUF_SIZE/2];
unsigned long spacing[1024*1024];
unsigned long buf2[BUF_SIZE/2];
unsigned long *bufpa;
unsigned long *bufpb;

unsigned long test_buffer_access(unsigned long* bufa, unsigned long* bufb, unsigned long test_size, long* sum) {
	unsigned long i;
	register unsigned long x;
	register unsigned char j;
	register long cumul = 0;
	unsigned long const runs = (unsigned long)(((float)RUN_TUNING)*(((float)RUN_BASE)/((float)test_size)));
	unsigned long runi = runs;

	while ( runi-- > 0 ) {
		for ( i = 0; i < test_size; i++) {
			for (j=0, x=bufa[i];j<CHAIN_LENGTH;j++,x=bufa[bufb[x]]) {
				cumul = cumul - ((long)bufb[x]);
				cumul = cumul + ((long)bufa[x]);
			}
		}
	}
	if (sum) { *sum = cumul; }
	return runs;
}

int main(int argc, char *argv[argc+1]) {
	clock_t		t;
	double		seq_seconds;
	double		rnd_seconds;
	long		sum;
	unsigned long	runs;

	if ( argc < 2 ) {
		fprintf(stderr, "Usage: %s bytes\n", argv[0]);
		return 2;
	}
	unsigned long const bytes = atol(argv[1]);
	if (bytes < MIN_BYTES ) {
		fprintf(stderr, "%s: bytes (%s) must be larger than %lu\n", argv[0], argv[1], MIN_BYTES-1);
		return 2;
	}
	if (bytes > MAX_BYTES ) {
		fprintf(stderr, "%s: bytes (%s) must be smaller than %lu\n", argv[0], argv[1], MAX_BYTES+1);
		return 2;
	}
	unsigned long const test_size = bytes / sizeof(long) / 2;

	/*** Test serial access */
	/*   Fill half the used part of buffer. Each element names it's twin */
	for (unsigned long i = 0; i < test_size-1; i++) {
		buf1[i] = i+1;
		buf2[i] = i;
	}
	buf1[test_size-1] = 0;
	buf2[test_size-1] = test_size-1;

	t = clock();
	runs = test_buffer_access(buf1, buf2, test_size, &sum);
	seq_seconds = (double)(clock() - t)/(double)CLOCKS_PER_SEC;
	printf("%s:_________________________________________________________________________________\n", argv[0]);
	printf("%s: %lu sequential scans of %lu bytes took %8.3lf seconds\n", argv[0], runs, bytes, seq_seconds);
	
	/* test random access */
	/*   Fill half the used part of buffer. Each element names a random positionon the orher buffer */
	srand(time(NULL));
	for (unsigned long i = 0; i < test_size; i++) {
		buf1[i] = (unsigned long)rand() % test_size;
		buf2[i] = rand() % test_size;
	}
	t = clock();
	runs = test_buffer_access(buf1, buf2, test_size, &sum);
	rnd_seconds = (double)(clock() - t)/(double)CLOCKS_PER_SEC;
	printf("%s: %lu random     scans of %lu bytes took %8.3lf seconds)\n", argv[0], runs, bytes, rnd_seconds);
	printf("%s:__________________________________________________________________________________\n", argv[0]);

	printf("%s: At %lu bytes random access took %7.1lf times sequential access.\n", argv[0], bytes, rnd_seconds/seq_seconds);
	printf("%s:__________________________________________________________________________________\n", argv[0]);
	printf("\n");
	
	return 0;
}


	


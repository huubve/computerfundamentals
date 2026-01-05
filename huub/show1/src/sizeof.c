#include <stdio.h>

int main( int argc, char ** argv) {

	printf("sizeof(char)     = %lu\n", sizeof(char));
	printf("sizeof(short)    = %lu\n", sizeof(short));
	printf("sizeof(int)      = %lu\n", sizeof(int));
	printf("sizeof(long int) = %lu\n", sizeof(long int));
	printf("sizeof(long)     = %lu\n", sizeof(long));
	printf("sizeof(long long)= %lu\n", sizeof(long long));
	printf("sizeof(float)    = %lu\n", sizeof(float));
	printf("sizeof(double)   = %lu\n", sizeof(double));
	printf("sizeof(void *)   = %lu\n", sizeof(void *));
	printf("sizeof(size_t)   = %lu\n", sizeof(size_t));
	printf("sizeof(int8_t)   = %lu\n", sizeof(int8_t));
	printf("sizeof(int16_t)  = %lu\n", sizeof(int16_t));
	printf("sizeof(int32_t)  = %lu\n", sizeof(int32_t));
	printf("sizeof(int64_t)  = %lu\n", sizeof(int64_t));
	return 0;
}

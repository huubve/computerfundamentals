#include <stdio.h>

static char * programName;

int main( int argc, [[maybe_unused]] char * argv[argc+1]) {

	for ( programName = argv[0]; *programName; programName++)
		fprintf(stderr, "%s: programName=%s\n", argv[0], programName);
	fprintf(stderr, "%s: programName=%s\n", argv[0], programName);

	for ( programName-- ; *programName != '/'; programName--)
		fprintf(stderr, "%s: programName=%s\n", argv[0], programName);
	fprintf(stderr, "%s: programName=%s\n", argv[0], programName);

	programName++;
	fprintf(stderr, "%s: programName=%s\n", argv[0], programName);

	printf("%s: My name is %s\n", programName, programName);

	return 0;
}

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define USAGE(name)	fprintf(stderr, "Usage: %s [-Dinlcq] PATTERN [file ...]\n", name)

#define INITIAL_LINE_BUF_SIZE 1

uint8_t	getOptions( int * argIndex, char * argv[] );
bool	grepInFile( char * pattern, FILE * f, char * fName, uint8_t options);
bool	lineMatches( char * s, char * p, uint8_t options);
bool	sStartsWithP( char * s, char * p, uint8_t options);

int	main( int argc, char * argv[argc+1]) {

	uint8_t	options = 0;

	bool	anyMatch = false;

	int	argIndex = 1;

	if ( ! argv[argIndex] ) {
		USAGE(argv[0]);
		return 2;
	}

	char *	pattern = argv[argIndex++]; // next argument is pattern to grep

	if ( argv[argIndex] ) {
		// there are filename arguments. loop them.
		FILE *	f = (FILE *)0;
		while ( argv[argIndex] ) {
			if ( (f = fopen(argv[argIndex], "r")) ) {
				anyMatch |= grepInFile(pattern, f, argv[argIndex], options);
			} else {
				perror(argv[argIndex]);
			}
			argIndex += 1;
		}
	} else {
		// no filenames. grep from stdin
		anyMatch = grepInFile(pattern, stdin, "", options);
	}
	return ( anyMatch ? EXIT_SUCCESS : EXIT_FAILURE );
}
	
bool	grepInFile( char * pattern, FILE * f, char * fName, uint8_t options) {

	size_t	bufSize = INITIAL_LINE_BUF_SIZE;
	char *	line = (char *)malloc(bufSize);
	ssize_t	r;
	size_t	nMatches = 0;
	while (true) {
		r = getline(&line, &bufSize, f);
		if ( r == -1 ) break; // EOF
		
		if ( lineMatches(line, pattern, options) ) {
			nMatches++;
			if ( *fName ) printf("%s:", fName);
			printf("%s\n", line);
		}
	}
	free(line);
	return ( nMatches > 0 );
}

bool lineMatches( char * line, char * pattern, uint8_t options) {
	bool	match = false;
	if ( ! *pattern ) match = true;
	while ( *line && ! match ) {
		match = sStartsWithP(line,pattern,options);
		line++;
	}
	return match;
}
	

inline bool	sStartsWithP( char * s, char * p, uint8_t options) {
	while (*s && *p ) {
		if ( *s != *p) return false;
		s++;
		p++;
	}
	if ( *p )
		return false;
	else
		return true;
}
	

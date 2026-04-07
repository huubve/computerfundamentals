#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "debug.h"

#define debug(format, ...) DEBUG( 1, "", format __VA_OPT__(,) __VA_ARGS__)

#define OPT_IGNORE_CASE (uint8_t)1

#define INITIAL_LINE_BUF_SIZE 1

FILE *	nextFile(FILE * f, char * fName);
bool	grepInFile(char * pattern, FILE * f, char * fName, uint8_t options);
bool	lineMatches( char * s, char * p, uint8_t options);
bool	sStartsWithP( char * s, char * p, uint8_t options);

char *	myName;

int	main( int argc, char * argv[argc+1]) {

	char *	fName;
	uint8_t	options  = 0;
	bool	anyMatch = false;

	int	argIndex = 0;
	myName = strdup(argv[argIndex++]);

	bool	inFlags = true;
	while ( inFlags && argv[argIndex][0] == '-' ) {
		int	c = 1;
		while ( inFlags && argv[argIndex][c] ) {
			switch ( argv[argIndex][c] ) {
			case '-':
				inFlags = false;
				break;
			case 'D':
				DEBUG_LEVEL(1);
				c++;
				break;
			case 'i':
				options |= OPT_IGNORE_CASE;
				c++;
				break;
			}
		}
		argIndex++;
	}
	debug("options = %x\n", options);

	char *	pattern = argv[argIndex++]; // next argument is pattern to grep

	if ( (fName = argv[argIndex]) ) {
		// loop filename arguments
		FILE *	f = (FILE *)0;
		while ( (f = nextFile( f, fName)) ) {
			anyMatch |= grepInFile(pattern, f, fName, options);
			argIndex++;
		}
	} else {
		// no filenames => grep from stdin
		anyMatch = grepInFile(pattern, stdin, "", options);
	}
	return ( anyMatch ? EXIT_SUCCESS : EXIT_FAILURE );
}
	
FILE *	nextFile(FILE * f, char * fName) {
	if ( f ) fclose(f);
	if ( fName ) {
		if ( (f = fopen(fName, "r")) ) {
			return f;
		} else {
			perror(fName);
			return (FILE *)0;
		}
	} else {
		// no filename
		return (FILE *)0;
	}
}

bool	grepInFile( char * pattern, FILE * f, char * fName, uint8_t options) {

	size_t	bufSize = INITIAL_LINE_BUF_SIZE;
	char *	line = (char *)malloc(bufSize);
	ssize_t	r;
	size_t	lineNr = 0;
	bool	fileHasMatch = false;
	while (true) {
		lineNr++;
		r = getline(&line, &bufSize, f);
		debug("grepInFile: file='%s' lineNr=%zu r=%zd bufSize=%zu\n", fName, lineNr, r, bufSize);
		if ( r == -1 ) break; // EOF
		if ( line[r-1] == '\n' ) line[r-1] = '\0'; // strip newline
		
		if ( lineMatches(line, pattern, options) ) {
			fileHasMatch = true;
			if ( *fName ) printf("%s: ", fName);
			printf("%s\n", line);
		}
	}
	free(line);
	return fileHasMatch;
}

bool lineMatches( char * s, char * p, uint8_t options) {
	bool	match = false;
	debug("lineMatches: s = '%s' p = '%s'\n", s, p);
	if ( ! *p ) return true; // empty string matches anything
	while ( *s && ! match ) {
		match = sStartsWithP(s,p,options);
		s++;
	}
	return match;
}
	
#define CASE_BIT (unsigned char)32
inline bool	sStartsWithP( char * s, char * p, uint8_t options) {
	debug("sStartsWithP: s,p = %s %s\n", s, p);
	while (*s && *p ) {
		debug("sStartsWithP: *s,*p = %c %c\n", *s, *p);
		if ( options & OPT_IGNORE_CASE ) {
			char lowers = (*s) | CASE_BIT;
			char lowerp = (*p) | CASE_BIT;
			if ( 96 < lowers && lowers < 123 ) { // a-z
				debug("sStartsWithP: lowers,lowerp = %c %c\n", lowers, lowerp);
				if ( lowers != lowerp ) return false;
			} else {
				if ( *s != *p) return false;
			}
		} else {
			if ( *s != *p) return false;
		}
		s++;
		p++;
	}
	if ( *p )
		return false;
	else
		return true;
}
	

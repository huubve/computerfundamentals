#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define USAGE(name)	fprintf(stderr, "Usage: %s [-Dinlcq] PATTERN [file ...]\n", name)

#define OPT_IGNORE_CASE		(uint8_t)1
#define OPT_PRINT_LINE		(uint8_t)2
#define OPT_PRINT_LINENR	(uint8_t)4
#define OPT_PRINT_FNAME		(uint8_t)8
#define OPT_PRINT_MATCH_COUNT	(uint8_t)16
#define OPT_NO_PRINT		(uint8_t)32

#define INITIAL_LINE_BUF_SIZE 1

uint8_t	getOptions( int * argIndex, char * argv[] );
bool	grepInFile( char * pattern, FILE * f, char * fName, uint8_t options);
bool	lineMatches( char * s, char * p, uint8_t options);
bool	sStartsWithP( char * s, char * p, uint8_t options);

int	main( int argc, char * argv[argc+1]) {

	bool	anyMatch = false;

	int	argIndex = 1;
	uint8_t	options  = getOptions(&argIndex, argv);

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
	
uint8_t	getOptions( int * argIndex, char * argv[] ) {
	uint8_t	options  = OPT_PRINT_LINE;
	bool	inFlags = true;
	while ( inFlags && argv[*argIndex] && argv[*argIndex][0] == '-' ) {
		if ( ! argv[*argIndex][1] ) {
			USAGE(argv[0]);
			exit(2);
		}
		int	c = 1;
		while ( inFlags && argv[*argIndex][c] ) {
			bool	skipToNextArg = false;
			switch ( argv[*argIndex][c] ) {
			case '-':
				inFlags = false;
				break;
			case 'i':
				options |= OPT_IGNORE_CASE;
				break;
			case 'n':
				options |= OPT_PRINT_LINENR;
				break;
			case 'l':
				options |= OPT_PRINT_FNAME;
				break;
			case 'c':
				options |= OPT_PRINT_MATCH_COUNT;
				break;
			case 'q':
				options |= OPT_NO_PRINT;
				break;
			default:
				USAGE(argv[0]);
				exit(2);
			}
			if ( skipToNextArg ) break;
			c++;
		}
		*argIndex += 1;
	}
	if ( options & ( OPT_PRINT_LINENR ) ) options &= ~ (OPT_PRINT_LINE);
	if ( options & ( OPT_PRINT_FNAME ) ) options &= ~ (OPT_PRINT_LINE | OPT_PRINT_LINENR);
	if ( options & ( OPT_PRINT_MATCH_COUNT ) ) options &= ~ (OPT_PRINT_LINE | OPT_PRINT_LINENR | OPT_PRINT_FNAME);
	if ( options & ( OPT_NO_PRINT ) ) options &= ~ (OPT_PRINT_LINE | OPT_PRINT_LINENR | OPT_PRINT_FNAME | OPT_PRINT_MATCH_COUNT);

	return options;
}

bool	grepInFile( char * pattern, FILE * f, char * fName, uint8_t options) {

	size_t	bufSize = INITIAL_LINE_BUF_SIZE;
	char *	line = (char *)malloc(bufSize);
	ssize_t	r;
	size_t	lineNr = 0;
	size_t	nMatches = 0;
	while (true) {
		lineNr++;
		r = getline(&line, &bufSize, f);
		if ( r == -1 ) break; // EOF
		if ( line[r-1] == '\n' ) line[r-1] = '\0'; // strip newline
		
		if ( lineMatches(line, pattern, options) ) {
			nMatches++;
			if ( options & OPT_PRINT_FNAME ) {
				if ( *fName ) printf("%s\n", fName);
				fflush(stdout);
				break;
			}
			if ( options & OPT_PRINT_LINE ) {
				if ( *fName ) printf("%s:", fName);
				printf("%s\n", line);
				fflush(stdout);
			}
			if ( options & OPT_PRINT_LINENR ) {
				if ( *fName ) printf("%s: ", fName);
				printf("%zu:%s\n", lineNr, line);
				fflush(stdout);
			}
		} else {
		}
	}
	if ( options & OPT_PRINT_MATCH_COUNT ) {
		if ( *fName ) printf("%s:", fName);
		printf("%zu\n",nMatches);
		fflush(stdout);
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
	#define CASE_BIT (unsigned char)32
	#define LOWER(c) ( ( 96 < ((c)|CASE_BIT) ) && ( ((c)|CASE_BIT) < 123 ) ? ((c)|CASE_BIT) : (c) )
	// shit happens when: #define LOWER(c) ( (c)|CASE_BIT ) (try (not) matching ~ and ^ )
	while (*s && *p ) {
		if ( options & OPT_IGNORE_CASE ) {
			if ( LOWER(*s) != LOWER(*p) ) return false;
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
	

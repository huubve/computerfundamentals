#include <stdbool.h>
#include <ctype.h>

extern int getoptions( int argc, char *argv[], char * optiondefinition);

/* value_u holds a single flag argument value */
typedef union {
		bool	b;
		char	c;
		char *	s;
		int32_t		i32;
		uint64_t	ui64;
		double	d;
} value_u;

/* flag_t describes a single flag
 */
typedef struct	flag_s {
	char		flag;
	bool		given;
	char		vformat[32];
	value_type_e	vtype;
	value_u		value;
	char		vseparator;
	uint32_t	vcount;
	value_u *	values;
} flag_t;

/* bits of this enum tell which member of value_u is used for the flag's argument
 * and whether the flag argument is a single value or a list */
typedef enum {
      LIST = 1, BOOL = 2, CHAR = 4, STRING = 8, I32 = 16, UI64 = 32, DOUBLE = 64
} value_type_e;

#define MAXFLAGS 128
static flag_t *	flags[MAXFLAGS]; /* one for every ASCII(7 bits) character */
static bool flags_initialised=false;

int	initflags(char * definition) {
	
	if ( flags_initialised ) return 1;

	for ( int i = 0; i < MAXFLAGS; i++ ) {
	}

	while (*definition) {
		char flag = *definition;
      		char *p = definition;
      		if (! isalnum(flag) ) return 0;
      		flags[flag] = (flag_t *)malloc(sizeof(flag_t));
		flags[flag]->flag = (char)flag;
		flags[flag]->given = false;
		flags[flag]->vformat[0] = (char)0;
		flags[flag]->vseparator = (char)0;
		flags[flag]->vtype = 0;
		flags[flag]->vcount = 0;
		flags[flag]->values = (value_u *)0;
      		definition++;
	}

}

int	getflags( int argc, char *argv[], int * nextarg) {

	int  optioni = nextoption ? *nextoption : 1;
	bool in_options = true;

	assert(flagsinitialised);
	
	for ( char ** arg = *argv[optioni]; **arg == '-' && in_options; arg++ ) {
		char *p = (*arg)+1;
		if ( ! *p ) {
			// todo error
			in_options = false;
			continue;
		}
		if ( *p == '-' ) {
			in_options = false;
			continue;
		}
		for (p++; isalnum(*p) && options[*p]; p++) {
		if ( *argv[i][1] == '-' ) {


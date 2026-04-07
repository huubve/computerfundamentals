#include <stdlib.h>
#include <stdio.h>

#define DEBUG(level, tag, format, ...) do { if ( DEBUG_EVAL(level, tag) ) { fprintf(stderr, format __VA_OPT__(,) __VA_ARGS__); } } while (0)
#define DEBUG_EVAL(level, tags)	debugState_(1, level, tags)
#define DEBUG_LEVEL(level)	debugState_(2, level, "")
#define DEBUG_TAG(tags)		debugState_(4, (uint8_t)0, tags)
#define DEBUG_UNTAG(tags)	debugState_(8, (uint8_t)0, tags)
#define DEBUG_ERROR		(uint8_t)128

uint8_t	debugState_( uint8_t action, uint8_t level, char * tags) {
	//current implementation only supports checking level. no tags yet
	//static char *	debugTags[] = {};
	static uint8_t	debugLevel = 0;
	uint8_t		returnLevel;

	switch ( action ) {
		case 1: // eval
			if ( debugLevel >= level ) {
				return (uint8_t)true;
			} else {
				return (uint8_t)false;
			}
		case 2: // set level
			returnLevel = debugLevel;
			debugLevel = level;
			return returnLevel;
		case 3: // add tags not implemented
		case 4: // drop tags not implemented
		default:
			return DEBUG_ERROR;
	}
}
		

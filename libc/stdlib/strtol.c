#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

long strtol(char* string, char* pointer, int base) {

    unsigned long result = 0;
    uint16_t character = 0;

    /* If non-zero, number is negative. */
    int negative = 0;

    /* Cut out any whitespace. */
    while(isspace(character)) {
        *string++;
    }

    /* Detect if negative. */
    if(character == '-') {
        negative = 1;
        *string++;
    } else if(character == '+') {
        *string++;
    }

    /* Handle base. */
/*
    if((base == 0 || base == 16) && c == '0' && (*s == 'x' || *s == 'X')) {
		c = s[1];
		s += 2;
		base = 16;
	}
*/

    if(base == 0) {

    }

    return result;
}

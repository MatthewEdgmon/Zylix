#include <ctype.h>
#include <stdlib.h>
#include <stdint.h>

int atoi(const char* string) {
    int number = 0, is_negative = 0;
    while(isspace(*string)) {
        string++;
    }

    switch(*string) {
        case '-':
            is_negative = 1;
        case '+':
            string++;
    }

    /* Compute n as a negative number to avoid overflow on INT_MIN */
	while (isdigit(*string)) {
		number = 10 * number - (*string++ - '0');
    }

    return is_negative ? number : -number;
}

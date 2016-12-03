#include <string.h>

char* strtok(char* s1, const char* s2) {
    static char* tmp = NULL;
    const char* p = s2;

    if(s1 != NULL) {
        /* new string */
        tmp = s1;
    } else {
        /* old string continued */
        if(tmp == NULL) {
            /* No old string, no new string, nothing to do */
            return NULL;
        }
        s1 = tmp;
    }

    /* skipping leading s2 characters */
    while(*p && *s1) {
        if(*s1 == *p) {
            /* found seperator; skip and start over */
            ++s1;
            p = s2;
            continue;
        }
        ++p;
    }

    if(!*s1) {
        /* no more to parse */
        return ( tmp = NULL );
    }

    /* skipping non-s2 characters */
    tmp = s1;
    while(*tmp) {
        p = s2;
        while(*p) {
            if(*tmp == *p++) {
                /* found seperator; overwrite with '\0', position tmp, return */
                *tmp++ = '\0';
                return s1;
            }
        }
        ++tmp;
    }

    /* parsed to end of string */
    tmp = NULL;
    return s1;
}

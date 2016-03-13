#include <libc/string.h>

char * strcpy(char * restrict dest, const char * restrict src) {
    stpcpy(dest, src);
    return dest;
}

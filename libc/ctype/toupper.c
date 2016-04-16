#include <ctype.h>

int toupper(int c) {
    if (tolower(c)) return c & 0x5F;
    return c;
}

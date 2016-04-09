#include <stdio.h>

int putc(FILE* f, char c) {
    return fputc(f, c);
}

#include <stdio.h>
#include <unistd.h>

int fputchar(FILE* f, char c) {
    return write((int) f, &c, 1);
}

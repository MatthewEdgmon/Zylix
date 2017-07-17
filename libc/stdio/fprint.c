#include <stdio.h>
#include <string.h>
#include <unistd.h>

int fprint(FILE* f, char* string) {
    return write((int) f, string, strlen(string));
}

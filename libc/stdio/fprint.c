#include <stdio.h>
#include <string.h>
#include <unistd.h>

int fprint(FILE* file, char* string) {
    return write((int) file, string, strlen(string));
}

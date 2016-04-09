#include <stdio.h>

int getc(FILE* stream) {
    char input_char;
    int status = read((int) stream, &input_char, 1);

    if(status) {
        return status;
    }

    return input_char;
}

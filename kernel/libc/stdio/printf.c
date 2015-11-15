#include <libc/stdbool.h>
#include <libc/stdarg.h>
#include <libc/stddef.h>
#include <libc/stdio.h>
#include <libc/string.h>

static void print(const char* data, size_t data_length) {
    for(size_t i = 0; i < data_length; i++) {
        putchar((int) ((const unsigned char*) data)[i]);
    }
}

int printf(const char* restrict format, ...) {

    va_list parameters;
    va_start(parameters, format);

    int written = 0;
    size_t amount;
    bool rejected_bad_specifier = false;

    while(*format != '\0') {
        if(*format != '%') {

        }
    }

    va_end(parameters);

    return written;
}
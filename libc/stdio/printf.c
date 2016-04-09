#include <stdarg.h>
#include <stdio.h>

int printf(const char* fmt, ...) {
    va_list va_args;
    int return_value = 0;

    va_start(va_args, fmt);
    return_value = vprintf(fmt, va_args);
    va_end(va_args);

    return return_value;
}

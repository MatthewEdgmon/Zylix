#include <stdarg.h>
#include <stdio.h>

int vprintf_help(unsigned c, void **ptr) {
	return putc(stdout, c);
}

int vprintf(const char *fmt, va_list va_args) {
	return printf_format(fmt, va_args, vprintf_help, NULL);
}

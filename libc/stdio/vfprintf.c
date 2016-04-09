#include <stdarg.h>
#include <stdio.h>

int vfprintf_help(unsigned c, void **ptr) {
	return fputc(c, ptr);
}

int vfprintf(FILE* file, const char *fmt, va_list va_args) {
	return printf_format(fmt, va_args, vfprintf_help, NULL);
}

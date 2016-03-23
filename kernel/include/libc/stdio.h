#ifndef __STDIO_H__
#define __STDIO_H__

#define EOF (-1)

#ifdef __cplusplus
extern "C" {
#endif

#include <libc/stdarg.h>

typedef int (*printf_func_ptr)(unsigned c, void** helper);

int do_printf(const char* fmt, va_list va_args, printf_func_ptr func, void* ptr);

int printf(const char* restrict fmt, ...);
int sprintf(char *buffer, const char *fmt, ...);

int vprintf(const char *fmt, va_list va_args);
int vsprintf(char *buffer, const char *fmt, va_list args);

int putc(int ic);
int puts(const char* string);
char getc();
char* gets(char* string);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __STDIO_H__ */

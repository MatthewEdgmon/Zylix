#ifndef __STDIO_H__
#define __STDIO_H__

#define EOF (-1)

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
#define NULL 0L
#else
#define NULL ((void*)0)
#endif

#undef EOF
#define EOF (-1)

#undef SEEK_SET
#undef SEEK_CUR
#undef SEEK_END
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

typedef unsigned int FILE;

typedef unsigned long size_t;

extern FILE* stdin;
extern FILE* stdout;
extern FILE* stderr;

#define stdin   (stdin)
#define stdout  (stdout)
#define stderr  (stderr)

#include <stdarg.h>

typedef int (*printf_func_ptr)(unsigned c, void** helper);

int printf_format(const char* fmt, va_list va_args, printf_func_ptr func, void* ptr);

/* File management. */
FILE* fopen(const char* name, const char* mode);
int fclose(FILE *f);

/* File input. */
int fgetc(FILE* f);
int fgetchar(FILE* f);
char* fgets(char* buffer, int size, FILE* f);

/* File output. */
int putc(FILE* f, char c);
int fputc(FILE* f, char c);
int fputchar(FILE* f, char c);
int vfprintf(FILE* f, const char *fmt, va_list va_args);

/* Terminal output. */
int puts(const char* string);
int printf(const char* restrict fmt, ...);
int vprintf(const char *fmt, va_list va_args);

/* Terminal input. */
int getc(FILE* stream);
char* gets(char* string);

/* Buffer output. */
int sprintf(char *buffer, const char *fmt, ...);
int vsprintf(char *buffer, const char *fmt, va_list args);
int vsnprintf(char *buffer, const char *fmt, va_list args);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __STDIO_H__ */
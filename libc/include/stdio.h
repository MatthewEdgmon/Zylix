/**
 * stdio.h - I/O
 *
 * This file is part of Zylix.
 *
 * Zylix is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Zylix is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Zylix.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __STDIO_H__
#define __STDIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Define size_t if it's undefined. */
#ifndef LIBC_SIZE_T_DEFINED
#define LIBC_SIZE_T_DEFINED
typedef unsigned long size_t;
#endif /* LIBC_SIZE_T_DEFINED */

/* Define NULL if it's undefined. */
#ifndef LIBC_NULL_DEFINED
#define LIBC_NULL_DEFINED
#ifdef __cplusplus
#define NULL 0L
#else
#define NULL ((void*)0)
#endif /* __cplusplus */
#endif /* LIBC_NULL_DEFINED */

#undef EOF
#define EOF (-1)

#undef SEEK_SET
#undef SEEK_CUR
#undef SEEK_END
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

typedef unsigned int FILE;

extern FILE* stdin;
extern FILE* stdout;
extern FILE* stderr;

#define stdin   (stdin)
#define stdout  (stdout)
#define stderr  (stderr)

#include <stdarg.h>

typedef int (*printf_func_ptr)(unsigned c, void** helper);

int printf_format(const char* fmt, va_list va_args, printf_func_ptr func, void* ptr);

FILE* fopen(const char* name, const char* mode);
int fclose(FILE *f);

int feof(FILE *);
int ferror(FILE *);
int fflush(FILE *);

int fseek(FILE *, long, int);
long ftell(FILE *);
void rewind(FILE *);

int fgetc(FILE* f);
int fgetchar(FILE* f);
char* fgets(char* buffer, int size, FILE* f);

int setvbuf(FILE *, char *, int, size_t);
void setbuf(FILE *, char *);


int fputc(FILE* f, char c);
int fputchar(FILE* f, char c);
int fprint(FILE* f, char* string);
int fprintf(FILE* f, const char* fmt, ...);
int vfprintf(FILE* f, const char *fmt, va_list va_args);

int putc(FILE* f, char c);
int putchar(char c);
int puts(const char* string);
int print(char* string);
int printf(const char* restrict fmt, ...);
int vprintf(const char *fmt, va_list va_args);

int getc(FILE* stream);
char* gets(char* string);

int sprintf(char *buffer, const char *fmt, ...);
int vsprintf(char *buffer, const char *fmt, va_list args);
int vsnprintf(char *buffer, const char *fmt, va_list args);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __STDIO_H__ */

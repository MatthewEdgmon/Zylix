#ifndef __STDIO_H__
#define __STDIO_H__

#define EOF (-1)

#ifdef __cplusplus
extern "C" {
#endif

typedef int (*printf_func_ptr)(unsigned c, void** helper);

int printf(const char* restrict fmt, ...);

int putc(int ic);
int puts(const char* string);
char getc();
char* gets(char* string);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __STDIO_H__ */

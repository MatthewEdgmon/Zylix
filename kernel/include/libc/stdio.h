#ifndef __STDIO_H__
#define __STDIO_H__

int printf(const char* restrict format, ...);
int putc(int ic);
int puts(const char* string);
char getc();
void gets(char* string);

#endif /* __STDIO_H__ */
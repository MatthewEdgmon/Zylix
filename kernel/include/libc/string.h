#ifndef __STRING_H__
#define __STRING_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
#define NULL 0L
#else
#define NULL ((void*)0)
#endif

#include <libc/stddef.h>

void* memset(void* buffer_pointer, int value, size_t size);

char * stpcpy(char * restrict d, const char * restrict s);
int strcmp(const char * l, const char * r);
char * strcpy(char * restrict dest, const char * restrict src);
size_t strlen(const char* string);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __STRING_H__ */

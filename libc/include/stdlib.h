#ifndef __STDLIB_H__
#define __STDLIB_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
#define NULL 0L
#else
#define NULL ((void*)0)
#endif

typedef unsigned long size_t;

void* malloc(size_t size);
void  free(void* address);

int atoi(const char* string);

long strtol(char* string, char* pointer, int base);

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

#define RAND_MAX (0x7FFFFFFF)

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __STDLIB_H__ */

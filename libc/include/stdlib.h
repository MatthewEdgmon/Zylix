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

#define RAND_MAX (0x7FFFFFFF)

static unsigned long int rand_seed = 1;

typedef unsigned long size_t;

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

int atoi(const char*);
long atol(const char*);
long long atoll(const char*);
double atof(const char*);

float strtof(const char*, char**);
long strtol(char*, char*, int);

int rand(void);
void srand(unsigned);

void* malloc(size_t);
void* calloc(size_t);
void* realloc(void*, size_t);
void  free(void*);

void abort(void);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __STDLIB_H__ */

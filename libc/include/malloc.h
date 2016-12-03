#ifndef __MALLOC_H__
#define __MALLOC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

void* malloc(size_t);
void* calloc(size_t, size_t);
void* realloc(void*, size_t);
void free(void*);
void* valloc(size_t);
void* memalign(size_t, size_t);

#ifdef __cplusplus
}
#endif

#endif /* __MALLOC_H__ */

#ifndef __LIBC_H__
#define __LIBC_H__

#include <types.h>

void * memcpy(void * restrict dest, const void * restrict src, size_t n);
void * memset(void * dest, int c, size_t n);
int memcmp(const void * vl, const void * vr, size_t n);

#endif /* __LIBC_H__ */
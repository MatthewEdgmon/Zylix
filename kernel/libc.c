/**
 * Minimal kernel libc, blueprint for future libc
 */

#include <types.h>

void * memcpy(void * restrict dest, const void * restrict src, size_t n) {
    __asm__ volatile("rep movsb"
                    : "=c"((int){0})
                    : "D"(dest), "S"(src), "c"(n)
                    : "flags", "memory");
    return dest;
}

void * memset(void * dest, int c, size_t n) {
    __asm__ volatile("rep stosb"
                    : "=c"((int){0})
                    : "D"(dest), "a"(c), "c"(n)
                    : "flags", "memory");
    return dest;
}

int memcmp(const void * vl, const void * vr, size_t n) {
    const unsigned char *l = vl;
    const unsigned char *r = vr;
    for (; n && *l == *r; n--, l++, r++);
    return n ? *l-*r : 0;
}
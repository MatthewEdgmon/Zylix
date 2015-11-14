#include <libc.h>

#include <limits.h>

#define ALIGN (sizeof(size_t))
#define ONES ((size_t)-1/UCHAR_MAX)
#define HIGHS (ONES * (UCHAR_MAX/2+1))
#define HASZERO(X) (((X)-ONES) & ~(X) & HIGHS)

#define BITOP(A, B, OP) \
 ((A)[(size_t)(B)/(8*sizeof *(A))] OP (size_t)1<<((size_t)(B)%(8*sizeof *(A))))

#define asm __asm__
#define volatile __volatile__

void * memcpy(void * restrict dest, const void * restrict src, size_t n) {
    asm volatile("rep movsb"
                : "=c"((int){0})
                : "D"(dest), "S"(src), "c"(n)
                : "flags", "memory");
    return dest;
}

void * memset(void * dest, int c, size_t n) {
    asm volatile("rep stosb"
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

void * memchr(const void * src, int c, size_t n) {
    const unsigned char * s = src;
    c = (unsigned char)c;
    for (; ((uintptr_t)s & (ALIGN - 1)) && n && *s != c; s++, n--);
    if (n && *s != c) {
        const size_t * w;
        size_t k = ONES * c;
        for (w = (const void *)s; n >= sizeof(size_t) && !HASZERO(*w^k); w++, n -= sizeof(size_t));
        for (s = (const void *)w; n && *s != c; s++, n--);
    }
    return n ? (void *)s : 0;
}

void * memrchr(const void * m, int c, size_t n) {
    const unsigned char * s = m;
    c = (unsigned char)c;
    while (n--) {
        if (s[n] == c) {
            return (void*)(s+n);
        }
    }
    return 0;
}

void * memmove(void * dest, const void * src, size_t n) {
    char * d = dest;
    const char * s = src;

    if (d==s) {
        return d;
    }

    if (s+n <= d || d+n <= s) {
        return memcpy(d, s, n);
    }

    if (d<s) {
        if ((uintptr_t)s % sizeof(size_t) == (uintptr_t)d % sizeof(size_t)) {
            while ((uintptr_t)d % sizeof(size_t)) {
                if (!n--) {
                    return dest;
                }
                *d++ = *s++;
            }
            for (; n >= sizeof(size_t); n -= sizeof(size_t), d += sizeof(size_t), s += sizeof(size_t)) {
                *(size_t *)d = *(size_t *)s;
            }
        }
        for (; n; n--) {
            *d++ = *s++;
        }
    } else {
        if ((uintptr_t)s % sizeof(size_t) == (uintptr_t)d % sizeof(size_t)) {
            while ((uintptr_t)(d+n) % sizeof(size_t)) {
                if (!n--) {
                    return dest;
                }
                d[n] = s[n];
            }
            while (n >= sizeof(size_t)) {
                n -= sizeof(size_t);
                *(size_t *)(d+n) = *(size_t *)(s+n);
            }
        }
        while (n) {
            n--;
            d[n] = s[n];
        }
    }

    return dest;
}
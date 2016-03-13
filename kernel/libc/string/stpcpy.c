#include <limits.h>
#include <libc/common.h>
#include <libc/stdint.h>
#include <libc/string.h>

char * stpcpy(char * restrict d, const char * restrict s) {
    size_t * wd;
    const size_t * ws;

    if ((uintptr_t)s % ALIGN == (uintptr_t)d % ALIGN) {
        for (; (uintptr_t)s % ALIGN; s++, d++) {
            if (!(*d = *s)) {
                return d;
            }
        }
        wd = (void *)d;
        ws = (const void *)s;
        for (; !HASZERO(*ws); *wd++ = *ws++);
        d = (void *)wd;
        s = (const void *)ws;
    }

    for (; (*d=*s); s++, d++);

    return d;
}

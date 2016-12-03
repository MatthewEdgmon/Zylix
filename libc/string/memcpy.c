#include <string.h>
#include <stdint.h>

void* memcpy(void* dest, const void* src, size_t n) {
    unsigned char* d = dest;
    const unsigned char* s = src;
    for (; n; n--) *d++ = *s++;
	return dest;
}

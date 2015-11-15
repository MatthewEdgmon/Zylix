#include <libc/string.h>

#ifndef KERNEL_LIBC_USE_ASSEMBLY

void* memset(void* buffer_pointer, int value, size_t size) {
    unsigned char* buffer = (unsigned char*) buffer_pointer;
    for(size_t i = 0; i < size; i++) {
        buffer[i] = (unsigned char) value;
    }
    return buffer_pointer;
}

#endif

#ifdef KERNEL_LIBC_USE_ASSEMBLY

void* memset(void* buffer_pointer, int value, size_t size) {
    __asm__ __volatile__(
        "rep stosb"
        : "=c"((int){0})
        : "D"(buffer_pointer), "a"(value), "c"(size)
        : "flags", "memory");
    return buffer_pointer;
}

#endif
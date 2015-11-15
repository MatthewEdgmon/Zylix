#ifndef __STRING_H__
#define __STRING_H__

#include <libc/stddef.h>

void* memset(void* buffer_pointer, int value, size_t size);

size_t strlen(const char* string);

#endif /* __STRING_H__ */
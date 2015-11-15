#include <libc/string.h>

#include <libc/stdint.h>
#include <libc/stddef.h>

size_t strlen(const char* string) {
    size_t result = 0;
    while(string[result]) {
        result++;
    }
    return result;
}

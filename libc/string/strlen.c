#include <string.h>

#include <stdint.h>
#include <stddef.h>

size_t strlen(const char* string) {
    size_t result = 0;
    while(string[result]) {
        result++;
    }
    return result;
}

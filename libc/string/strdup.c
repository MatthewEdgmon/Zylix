#include <string.h>
#include <stdlib.h>

char* strdup(const char* src) {
    size_t length = strlen(src) + 1;
    char* string = malloc(length);
    if(string == NULL) {
        return NULL;
    }
    return (char*)memcpy(string, src, length);
}

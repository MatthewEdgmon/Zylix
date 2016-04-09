#include <stdio.h>
#include <unistd.h>

char* gets(char* buffer) {
    return fgets(buffer, 0xFFFFFFFF, stdin);
}

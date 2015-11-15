#include <libc/stdio.h>

#include <devices/ps2.h>
#include <devices/ps2keyboard.h>

void gets(char* string) {
    int i = 0;

    char ch;

    /* Always start with a null terminated string, just to be safe. */
    string[i] = '\0';

    while(1) {

    }
}
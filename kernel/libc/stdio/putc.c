#include <libc/stdio.h>

#include <terminal.h>

int putc(int ic) {
    char c = (char) ic;
    TerminalPrintCharacter(c);
    return ic;
}

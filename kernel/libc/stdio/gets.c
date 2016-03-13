#include <libc/stdio.h>

#include <devices/ps2.h>
#include <devices/ps2keyboard.h>

#include <terminal.h>

char* gets(char* string) {
    int i = 0;
    char current_char = 'A';

    while(current_char != '\n') {
        current_char = 'B';
        //current_char = getc();
        while(current_char != EOF) {
            string[i] = current_char;
            i++;
            TerminalPrintString("C");
        }
        TerminalPrintString("D");
    }

    return string;
}

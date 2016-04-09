#include <stdint.h>
#include <stdio.h>

#include <error.h>

#include <terminal.h>
#include <vga.h>

void KernelPanic(char* message) {
    TerminalSetColor(TerminalMakeColor(COLOR_LIGHT_RED, COLOR_BLACK));
    printf("Zylix has encountered an unrecoverable error: %s\n", message);
    printf("Stopping execution.\n");
    __asm__ __volatile__ ("cli");
    __asm__ __volatile__ ("hlt");
}

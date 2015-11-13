#include <error.h>

#include <types.h>
#include <common.h>
#include <terminal.h>
#include <vga.h>

void KernelPanic(char* message) {
    TerminalSetColor(TerminalMakeColor(COLOR_LIGHT_RED, COLOR_BLACK));
    TerminalPrintString("Zylix has encountered an unrecoverable error.\n");
    TerminalPrintString(message);
    HALT();
}
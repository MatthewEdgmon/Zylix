#ifndef __TERMINAL_H__
#define __TERMINAL_H__

#include <stdint.h>

#include <devices/vga.h>

uint8_t TerminalMakeColor(enum vga_color foreground, enum vga_color background);

void TerminalClear();
void TerminalSetColor(uint8_t color);
void TerminalNewLine();
void TerminalPrintCharacter(char character);
void TerminalPrintString(char* string);
void SetupTerminal();

#endif /* __TERMINAL_H__ */

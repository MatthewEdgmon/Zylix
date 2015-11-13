#ifndef __TERMINAL_H__
#define __TERMINAL_H__

#include <stddef.h>
#include <types.h>

void TerminalClear();
void TerminalSetColor(uint8_t color);
void TerminalNewLine();
void TerminalPrintCharacter(char character);
void TerminalPrintString(char* string);
void SetupTerminal();

#endif /* __TERMINAL_H__ */
/**
 * terminal.h - x86 text terminal emulation.
 *
 * This file is part of Zylix.
 *
 * Zylix is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Zylix is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Zylix.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __TERMINAL_H__
#define __TERMINAL_H__

#include <stdint.h>

#include <devices/video/vga.h>

uint8_t TerminalMakeColor(enum vga_color foreground, enum vga_color background);

void LFBTerminalSetBPP(uint32_t bbp);

void TerminalClear();
void TerminalSetColor(uint8_t color);
void TerminalNewLine();
void TerminalPrintCharacter(char character);
void TerminalPrintString(char* string);
void SetupTerminal();

#endif /* __TERMINAL_H__ */

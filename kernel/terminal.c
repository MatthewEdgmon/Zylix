/**
 * terminal.c
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

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include <terminal.h>

#include <devices/video/vga.h>

bool      terminal_caught_escape;
size_t    terminal_row;
size_t    terminal_column;
uint8_t   terminal_color;
uint16_t* terminal_buffer;

uint8_t TerminalMakeColor(enum vga_color foreground, enum vga_color background) {
    return foreground | background << 4;
}

void TerminalSetColor(uint8_t color) {
    terminal_color = color;
}

uint16_t TerminalMakeVGAEntry(char c, uint8_t color) {
    uint16_t c16 = c;
    uint16_t color16 = color;
    return c16 | color16 << 8;
}

void TerminalMakeVGAEntryAt(char c, uint8_t color, size_t x, size_t y) {
    const size_t index = y * VGAGetTextModeWidth() + x;
    terminal_buffer[index] = TerminalMakeVGAEntry(c, color);
}

void TerminalClear() {
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = TerminalMakeColor(COLOR_LIGHT_GREY, COLOR_BLACK);

    for(size_t y = 0; y < VGAGetTextModeHeight(); y++) {
        for(size_t x = 0; x < VGAGetTextModeWidth(); x++) {
            TerminalMakeVGAEntryAt(' ', COLOR_BLACK, x, y);
        }
    }
}

void TerminalScroll() {
    if(terminal_row >= VGAGetTextModeHeight()) {
        /* Move the current buffer up by one line. */
        for(size_t i = 0 * VGAGetTextModeWidth(); i < (VGAGetTextModeHeight() - 1) * VGAGetTextModeWidth(); i++) {
            terminal_buffer[i] = terminal_buffer[i + VGAGetTextModeWidth()];
        }
        /* Make the new line blank. */
        for(size_t i = (VGAGetTextModeHeight() - 1) * VGAGetTextModeWidth(); i < VGAGetTextModeHeight() * VGAGetTextModeWidth(); i++) {
            terminal_buffer[i] = TerminalMakeVGAEntry(' ', COLOR_BLACK);
        }
        /* And finally set the current line to the second to last one. */
        terminal_row = (VGAGetTextModeHeight() - 1);
    }
}

void TerminalPrintCharacter(char character) {

    switch(character) {
        /* Alrarm/bell .*/
        case '\a':
            terminal_caught_escape = true;
            break;
        /* Backspace. */
        case '\b':
            /* C standard doesn't define behaivor for backspace at initial position. */
            /* I just ignore it. */
            if(terminal_column > 0) {
                terminal_column--;
            }
            TerminalMakeVGAEntryAt(' ', terminal_color, terminal_column, terminal_row);
            terminal_caught_escape = true;
            break;
        /* Formfeed? */
        case '\f':
            terminal_caught_escape = true;
            break;
        /* New line. */
        case '\n':
            terminal_row++;
            terminal_column = 0;
            terminal_caught_escape = true;
            TerminalScroll();
            break;
        /* Carriage return. */
        case '\r':
            terminal_column = 0;
            terminal_caught_escape = true;
            break;
        /* Horizontal tab. */
        case '\t':
            terminal_column += 8;
            break;
        /* Vertical tab. */
        case '\v':
            /* Move 6 lines vertically. */
            for(size_t i = 0; i < 6; i++) {
                terminal_row++;
                TerminalScroll();
            }
            break;
        /* Backslash. */
        case '\\':
            TerminalMakeVGAEntryAt(0x5C, terminal_color, terminal_column, terminal_row);
            terminal_caught_escape = false;
            break;
        /* Single quotation mark. */
        case '\'':
            TerminalMakeVGAEntryAt(0x27, terminal_color, terminal_column, terminal_row);
            terminal_caught_escape = false;
            break;
        /* Double quotation mark. */
        case '\"':
            TerminalMakeVGAEntryAt(0x22, terminal_color, terminal_column, terminal_row);
            terminal_caught_escape = false;
            break;
        /* Question mark. */
        case '\?':
            TerminalMakeVGAEntryAt(0x3F, terminal_color, terminal_column, terminal_row);
            terminal_caught_escape = false;
            break;
        /* NOT an escape code character. */
        default:
            TerminalMakeVGAEntryAt(character, terminal_color, terminal_column, terminal_row);
            terminal_caught_escape = false;
            break;
    }

    /* Certain escape characters aren't meant to be printed. */
    if(terminal_caught_escape)
        return;

    if(++terminal_column == VGAGetTextModeWidth() && terminal_row == VGAGetTextModeHeight()) {
        TerminalScroll();
    }
}

void TerminalPrintString(char* string) {
    size_t stringlen = strlen(string);
    for(size_t i = 0; i < stringlen; i++) {
        TerminalPrintCharacter(string[i]);
    }
}

/**
 * Initialize VGA terminal values to 0, then blank out the screen.
 */
void SetupTerminal() {
    terminal_row = 0;
    terminal_column = 0;
    //terminal_buffer = (uint16_t*) 0xB8000;
    terminal_buffer = (uint16_t*) (VGAGetFramebufferSegment() * 16);
    terminal_color = TerminalMakeColor(COLOR_LIGHT_GREY, COLOR_BLACK);

    for(size_t y = 0; y < VGAGetTextModeHeight(); y++) {
        for(size_t x = 0; x < VGAGetTextModeWidth(); x++) {
            const size_t index = y * VGAGetTextModeHeight() + x;
            terminal_buffer[index] = TerminalMakeVGAEntry(' ', terminal_color);
        }
    }
}

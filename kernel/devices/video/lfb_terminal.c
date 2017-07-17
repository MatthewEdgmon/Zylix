/**
 * lfb_terminal.c - Linear Frame Buffer terminal
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

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <devices/video/bitmap_font.h>
#include <devices/video/lfb_terminal.h>

uint8_t lfb_terminal_enabled = 0;

uint32_t* lfb_address;

/* How many bits per pixel. e.g. 32 = 0xFFFFFFFF 0x00RRGGBB */
uint16_t lfb_bits_per_pixel;

/* Size of the VRAM. */
uint32_t lfb_vram_size_x = 0;
uint32_t lfb_vram_size_y = 0;

/* Size of the visible area of VRAM. */
uint32_t lfb_screen_size_x = 0;
uint32_t lfb_screen_size_y = 0;

/* How many characters fit on the screen vertically/horizontally. */
uint16_t lfb_terminal_width = 0;
uint16_t lfb_terminal_height = 0;

/* Holds the next (character, not pixel) position a character will be printed. */
uint16_t lfb_terminal_index_x = 0;
uint16_t lfb_terminal_index_y = 0;

/* If non-zero, is a character translated by LFBTerminalFormatCharacter */
/* e.g. \\ -> \ */
char escape_character;

/* 128 x 48 characters*/
char lfb_character_array[128 * 48];

uint8_t LFBTerminalIsEnabled() {
    return lfb_terminal_enabled;
}

void LFBTerminalSetBPP(uint32_t bpp) {
    lfb_bits_per_pixel = bpp;
}

void LFBTerminalSetBuffer(uint32_t* address) {
    lfb_address = address;
}

void LFBTerminalClear() {
    if(!LFBTerminalIsEnabled()) {
        return;
    }

    lfb_terminal_index_x = 0;
    lfb_terminal_index_y = 0;

    for(size_t y = 0; y < lfb_screen_size_y; y++) {
        for(size_t x = 0; x < lfb_screen_size_x; x++) {
            lfb_address[LFBTerminalCoordinateToOffset(x, y)] = 0;
        }
    }
}

uint32_t LFBTerminalCoordinateToOffset(uint16_t pixel_x, uint16_t pixel_y) {
    if(!LFBTerminalIsEnabled()) {
        return 0;
    }

    if(pixel_x >= lfb_screen_size_x) {
        return 0;
    }

    if(pixel_y >= lfb_screen_size_y) {
        return 0;
    }

    //uint32_t offset = (pixel_y * 1024 + pixel_x) * 32;
    uint32_t offset = (pixel_y * lfb_screen_size_x + pixel_x);

    return offset;
}

/**
 * If it returns 1, don't print it.
 */
uint8_t LFBTerminalFormatCharacter(char character) {
    switch(character) {
        /* Alrarm/bell .*/
        case '\a':
            return 1;
        /* Backspace. */
        case '\b':
            /* Ignored at 0. */
            if(lfb_terminal_index_x == 0) {
                printf("IGNORING BACKSPACE.\n");
                return 1;
            }
            /* Otherwise just print the next character one index left. */
            lfb_terminal_index_x--;
            LFBTerminalPrintCharacter(' ');
            lfb_terminal_index_x--;
            return 1;
        /* Formfeed? */
        case '\f':
            return 1;
        /* Newline */
        case '\n':
            LFBTerminalNewLine();
            return 1;
        /* Carriage Return */
        case '\r':
            lfb_terminal_index_x = 0;
            return 1;
        /* Horizontal tab. */
        case '\t':
            lfb_terminal_index_x += 8;
            return 1;
        /* Vertical tab. */
        case '\v':
            /* Move 6 lines vertically. */
            for(size_t i = 0; i < 6; i++) {
                LFBTerminalNewLine();
            }
            break;
        /* Backslash. */
        case '\\':
            escape_character = 0x5C;
            return 0;
        /* Single quotation mark. */
        case '\'':
            escape_character = 0x27;
            return 0;
        /* Double quotation mark. */
        case '\"':
            escape_character = 0x22;
            return 0;
        /* Question mark. */
        case '\?':
            escape_character = 0x3F;
            return 0;
        default:
            return 0;
    }
    return 1;
}

void LFBTerminalNewLine() {
    lfb_terminal_index_x = 0;
    lfb_terminal_index_y++;

    /* Check if this newline needs to scroll. */
    if(lfb_terminal_index_y >= lfb_terminal_height) {
        LFBTerminalScroll();
    }
}

void LFBTerminalScroll() {
    while(lfb_terminal_index_y >= lfb_terminal_height) {
        /* Copy the inner section of the screen and move it up one line. */
        uint32_t* source = lfb_address + (BITMAP_FONT_CHARACTER_HEIGHT * lfb_screen_size_x);
        uint32_t* destination = lfb_address;
        uint32_t size = 32 * BITMAP_FONT_CHARACTER_LENGTH * lfb_screen_size_x;

        memcpy(destination, source, size);

        lfb_terminal_index_y--;
    }
}

void LFBTerminalPrintCharacter(char input) {
    char character = input;

    if(!LFBTerminalIsEnabled()) {
        return;
    }

    /* Check to see if it's an escape code or other non-printable character. */
    if(LFBTerminalFormatCharacter(character) != 0) {
        return;
    }

    /* If LFBTerminalFormatCharacter wants us to use a different character, use it. */
    if(escape_character != 0) {
        character = escape_character;
        escape_character = 0;
    }

    /* Get a pointer to the bitmap of the character. */
    uint32_t* bitmap_font_character = LFBTerminalGetBitmap(character);

    /* pixel_x & pixel_y are the screen coordinates we are printing to. */
    uint32_t pixel_x = lfb_terminal_index_x * BITMAP_FONT_CHARACTER_WIDTH;
    uint32_t pixel_y = lfb_terminal_index_y * BITMAP_FONT_CHARACTER_HEIGHT;

    /* Print a pixel for every pixel in the bitmap. */
    for(size_t i = 0; i < BITMAP_FONT_CHARACTER_LENGTH; i++) {

        /* Check if we reached the final integer on this row. */
        if(pixel_x - (lfb_terminal_index_x * BITMAP_FONT_CHARACTER_WIDTH) == BITMAP_FONT_CHARACTER_WIDTH) {

            /* Go back the length of the character. */
            pixel_x -= BITMAP_FONT_CHARACTER_WIDTH;

            /* Start the next line. */
            pixel_y++;
        }

        /* Set this pixel to white. */
        LFBTerminalPrintPixel(pixel_x, pixel_y, bitmap_font_character[i]);

        /* Ready the next pixel in the bitmap. */
        pixel_x++;
    }

    /* Printed a charcter, add the width of a character to offset the next. */
    lfb_terminal_index_x++;

    /* Have we printed the maximum amount of characters for this line? */
    if(lfb_terminal_index_x == lfb_terminal_width) {
        LFBTerminalNewLine();
    }
}

void LFBTerminalPrintString(char* string) {
    if(!LFBTerminalIsEnabled()) {
        return;
    }

    size_t stringlen = strlen(string);
    for(uint32_t i = 0; i < stringlen; i++) {
        LFBTerminalPrintCharacter(string[i]);
    }
}

void LFBTerminalPrintPixel(uint16_t pixel_x, uint16_t pixel_y, uint32_t value) {
    lfb_address[LFBTerminalCoordinateToOffset(pixel_x, pixel_y)] = value;
}

uint32_t* LFBTerminalGetBitmap(char character) {
    /* Decode the character to it's bitmap. */
    for(size_t i = 0; i < bitmap_font_table_length; i++) {
        if(bitmap_font_table[i].character == character) {
            return bitmap_font_table[i].bitmap_font_character;
        }
    }

    return bitmap_font_20_blank;
}

void SetupLFBTerminal(uint32_t* address, uint32_t size_x, uint32_t size_y) {
    /* Enable LFB */
    lfb_terminal_enabled = 1;

    /* Set the LFB address. */
    lfb_address = address;

    /* Set the screen size. */
    lfb_screen_size_x = size_x;
    lfb_screen_size_y = size_y;

    /* Calculate how many characters can fit. */
    lfb_terminal_width = lfb_screen_size_x / BITMAP_FONT_CHARACTER_WIDTH;
    lfb_terminal_height = lfb_screen_size_y / BITMAP_FONT_CHARACTER_HEIGHT;

    /* Clear the video memory. */
    LFBTerminalClear();
}

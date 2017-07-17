/**
 * lfb_terminal.h - Linear Frame Buffer terminal
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

#ifndef __LFB_TERMINAL_H__
#define __LFB_TERMINAL_H__

#include <stdint.h>

uint8_t LFBTerminalIsEnabled();

void LFBTerminalClear();
uint32_t LFBTerminalCoordinateToOffset(uint16_t pixel_x, uint16_t pixel_y);
uint8_t LFBTerminalFormatCharacter(char character);
void LFBTerminalNewLine();
void LFBTerminalScroll();
void LFBTerminalSetBuffer(uint32_t* address);
void LFBTerminalPrintCharacter(char character);
void LFBTerminalPrintString(char* string);
void LFBTerminalPrintPixel(uint16_t pixel_x, uint16_t pixel_y, uint32_t value);
uint32_t* LFBTerminalGetBitmap(char character);

#endif /* __LFB_TERMINAL_H__ */

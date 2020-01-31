/**
 * vga.c
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
#include <stdlib.h>
#include <string.h>

#include <arch/io.h>

#include <devices/video/vga.h>
#include <devices/video/vga_mode_data.h>
#include <devices/video/vga_font_data.h>

#include <terminal.h>

#define	peekb(S,O)		*(unsigned char *)(16uL * (S) + (O))
#define	pokeb(S,O,V)		*(unsigned char *)(16uL * (S) + (O)) = (V)
#define	pokew(S,O,V)		*(unsigned short *)(16uL * (S) + (O)) = (V)
#define	_vmemwr(DS,DO,S,N)	memcpy((char *)((DS) * 16 + (DO)), S, N)

static uint16_t vga_graphics_width, vga_graphics_height;

static uint16_t vga_text_width = 80, vga_text_height = 25;

static void (*VGAGraphicsDrawPixel)(unsigned x, unsigned y, unsigned c);

static void vmemwr(uint8_t dst_off, uint8_t* source, uint8_t count) {
	_vmemwr(VGAGetFramebufferSegment(), dst_off, source, count);
}

static void vpokeb(uint8_t* address, uint8_t value) {
	pokeb(VGAGetFramebufferSegment(), address, value);
}

static unsigned vpeekb(uint8_t* address) {
	return peekb(VGAGetFramebufferSegment(), address);
}

void VGAPrintHelper(uint16_t* regs, uint32_t count) {
	uint32_t i = 0;
	printf("    ");
	for(; count != 0; count--) {
		printf("0x%02X,", *regs);
		i++;
		if(i >= 8) {
			i = 0;
			printf("\n    ");
		} else {
			printf(" ");
		}
		regs++;
	}
	printf("\n");
}

void VGAPrintRegisters(uint16_t* registers) {
	printf("unsigned char g_mode[] = {\n");
	printf("    /* MISC */\n");
	printf("    0x%02X,\n", *registers);
	registers++;
	printf("    /* SEQ */\n");
	VGAPrintHelper(registers, VGA_NUMBER_SEQ_REGISTERS);
	registers += VGA_NUMBER_SEQ_REGISTERS;
	printf("    /* CRTC */\n");
	VGAPrintHelper(registers, VGA_NUMBER_CRTC_REGISTERS);
	registers += VGA_NUMBER_CRTC_REGISTERS;
	printf("    /* GC */\n");
	VGAPrintHelper(registers, VGA_NUMBER_GC_REGISTERS);
	registers += VGA_NUMBER_GC_REGISTERS;
	printf("    /* AC */\n");
	VGAPrintHelper(registers, VGA_NUMBER_AC_REGISTERS);
	registers += VGA_NUMBER_AC_REGISTERS;
	printf("}\n");
}

/**
 * Read the contents of the VGA register state to the screen.
 */
void VGADumpRegisters() {
	uint16_t vga_state[VGA_NUMBER_REGISTERS];
	VGAReadRegisters(vga_state);
	VGAPrintRegisters(vga_state);
}

/**
 * Read the contents of the VGA register state into "registers".
 */
void VGAReadRegisters(uint16_t* registers) {

    /* Read miscellaneous register. */
    *registers = inb(VGA_MISC_READ);
    registers++;

    /* read sequencer registers. */
    for(size_t i = 0; i < VGA_NUMBER_SEQ_REGISTERS; i++) {
    	outb(VGA_SEQ_INDEX, i);
    	*registers = inb(VGA_SEQ_DATA);
    	registers++;
    }

    /* read CRTC registers. */
    for(size_t i = 0; i < VGA_NUMBER_CRTC_REGISTERS; i++) {
    	outb(VGA_CRTC_INDEX, i);
    	*registers = inb(VGA_CRTC_DATA);
    	registers++;
    }

    /* Read graphics controller registers. */
    for(size_t i = 0; i < VGA_NUMBER_GC_REGISTERS; i++) {
    	outb(VGA_GC_INDEX, i);
    	*registers = inb(VGA_GC_DATA);
    	registers++;
    }

    /* read attribute controller egisters */
    for(size_t i = 0; i < VGA_NUMBER_AC_REGISTERS; i++) {
		(void)inb(VGA_INSTAT_READ);
		outb(VGA_AC_INDEX, i);
		*registers = inb(VGA_AC_READ);
		registers++;
	}

    /* Lock 16-color palette and unblank display. */
    uint8_t discard = inb(VGA_INSTAT_READ);
    outb(VGA_AC_INDEX, 0x20);
}

void VGAWriteRegisters(uint16_t* registers) {

    /* Write miscellaneous register. */
    outb(VGA_MISC_WRITE, *registers);
    registers++;

    /* Write sequencer registers. */
    for(size_t i = 0; i < VGA_NUMBER_SEQ_REGISTERS; i++) {
    	outb(VGA_SEQ_INDEX, i);
    	outb(VGA_SEQ_DATA, *registers);
    	registers++;
    }

    /* Unlock CRTC registers. */
    outb(VGA_CRTC_INDEX, 0x03);
    outb(VGA_CRTC_DATA, inb(VGA_CRTC_DATA) | 0x80);
    outb(VGA_CRTC_INDEX, 0x11);
    outb(VGA_CRTC_DATA, inb(VGA_CRTC_DATA) & ~0x80);

    /* Make sure they remain unlocked. */
    registers[0x03] |= 0x80;
    registers[0x11] &= ~0x80;

    /* write CRTC registers */
    for(size_t i = 0; i < VGA_NUMBER_CRTC_REGISTERS; i++) {
    	outb(VGA_CRTC_INDEX, i);
    	outb(VGA_CRTC_DATA, *registers);
    	registers++;
    }

    /* Write graphics controller registers. */
    for(size_t i = 0; i < VGA_NUMBER_GC_REGISTERS; i++) {
    	outb(VGA_GC_INDEX, i);
    	outb(VGA_GC_DATA, *registers);
    	registers++;
    }

    /* Write attribute controller registers. */
    for(size_t i = 0; i < VGA_NUMBER_AC_REGISTERS; i++) {
    	uint8_t discard = inb(VGA_INSTAT_READ);
    	outb(VGA_AC_INDEX, i);
    	outb(VGA_AC_WRITE, *registers);
    	registers++;
    }

    /* Lock 16-color palette and unblank display. */
    uint8_t discard = inb(VGA_INSTAT_READ);
    outb(VGA_AC_INDEX, 0x20);
}

void VGAWriteFont(uint8_t* buffer, uint8_t font_height) {
    /* These are the registers we have to save and restore. */
    uint8_t seq2, seq4, gc4, gc5, gc6;

    outb(VGA_SEQ_INDEX, 2);
	seq2 = inb(VGA_SEQ_DATA);

    outb(VGA_SEQ_INDEX, 4);
	seq4 = inb(VGA_SEQ_DATA);

    /* turn off even-odd addressing (set flat addressing)
    assume: chain-4 addressing already off */
    outb(VGA_SEQ_DATA, seq4 | 0x04);

    outb(VGA_GC_INDEX, 4);
    gc4 = inb(VGA_GC_DATA);

    outb(VGA_GC_INDEX, 5);
    gc5 = inb(VGA_GC_DATA);
    /* turn off even-odd addressing */
    outb(VGA_GC_DATA, gc5 & ~0x10);

    outb(VGA_GC_INDEX, 6);
    gc6 = inb(VGA_GC_DATA);

    /* Turn off even-odd addressing. */
    outb(VGA_GC_DATA, gc6 & ~0x02);

    /* Write font to plane P4. */
    VGASetPlane(2);

    /* Write font. */
    for(size_t i = 0; i < 256; i++) {
        vmemwr(16384u * 0 + i * 32, buffer, font_height);
        buffer += font_height;
    }

#if 0
	for(size_t i = 0; i < 256; i++) {
        vmemwr(16384u * 1 + i * 32, buffer, font_height);
        buffer += font_height;
    }
#endif

    /* Restore registers. */
    outb(VGA_SEQ_INDEX, 2);
	outb(VGA_SEQ_DATA, seq2);
	outb(VGA_SEQ_INDEX, 4);
	outb(VGA_SEQ_DATA, seq4);
	outb(VGA_GC_INDEX, 4);
	outb(VGA_GC_DATA, gc4);
	outb(VGA_GC_INDEX, 5);
	outb(VGA_GC_DATA, gc5);
	outb(VGA_GC_INDEX, 6);
	outb(VGA_GC_DATA, gc6);
}

uint16_t VGAGetFramebufferSegment() {
    uint16_t segment = 0xA000;

    outb(VGA_GC_INDEX, 6);
    segment = inb(VGA_GC_DATA);
    segment >>= 2;
    segment &= 3;
    switch(segment) {
        default:
            break;
        case 0:
        case 1:
            segment = 0xA000;
            break;
        case 2:
            segment = 0xB000;
            break;
        case 3:
            segment = 0xB800;
            break;
    }
    return segment;
}

uint16_t VGAGetTextModeWidth() { return vga_text_width; }
uint16_t VGAGetTextModeHeight() { return vga_text_height; }
uint16_t VGAGetGraphicsModeWidth() { return vga_graphics_width; }
uint16_t VGAGetGraphicsModeHeight() { return vga_graphics_height; }

void VGASetPlane(uint8_t plane) {
    uint8_t plane_mask;

	plane &= 3;
	plane_mask = 1 << plane;
    /* Set read plane. */
	outb(VGA_GC_INDEX, 4);
	outb(VGA_GC_DATA, plane);
    /* Set write plane. */
	outb(VGA_SEQ_INDEX, 2);
	outb(VGA_SEQ_DATA, plane_mask);
}

void VGASetTextMode(uint8_t width, uint8_t height) {
    uint8_t font_height = 0;

	switch(width) {
		case 40:
			switch(height) {
				case 25:
					VGAWriteRegisters(vga_text_40_25);
					vga_text_width = 40;
					vga_text_height = 25;
					font_height = 16;
					break;
				case 50:
					VGAWriteRegisters(vga_text_40_50);
					vga_text_width = 40;
					vga_text_height = 50;
					font_height = 16;
					break;
			}
			break;
		case 80:
			switch(height) {
				case 25:
					VGAWriteRegisters(vga_text_80_25);
					vga_text_width = 80;
					vga_text_height = 25;
					font_height = 16;
					break;
				case 50:
					VGAWriteRegisters(vga_text_80_50);
					vga_text_width = 80;
					vga_text_height = 50;
					font_height = 16;
					break;
			}
			break;
		case 90:
			switch(height) {
				case 30:
					VGAWriteRegisters(vga_text_90_30);
					vga_text_width = 90;
					vga_text_height = 30;
					font_height = 8;
					break;
				case 60:
					VGAWriteRegisters(vga_text_90_60);
					vga_text_width = 90;
					vga_text_height = 60;
					font_height = 8;
					break;
			}
			break;
		default:
			printf("Tried to request an unknown text mode \"%dx%d\".\n", width, height);
			return;
			break;
	}

    /* Set font. */
    if(font_height >= 16) {
    	VGAWriteFont(vga_8x16_font, 16);
    } else {
    	VGAWriteFont(vga_8x8_font, 8);
    }

    /* tell the BIOS what we've done, so BIOS text output works OK */
    pokew(0x40, 0x4A, vga_text_width);	                     /* columns on screen */
    pokew(0x40, 0x4C, vga_text_width * vga_text_height * 2); /* framebuffer size */
    pokew(0x40, 0x50, 0);		                             /* cursor pos'n */
    pokeb(0x40, 0x60, font_height - 1);	                     /* cursor shape */
    pokeb(0x40, 0x61, font_height - 2);
    pokeb(0x40, 0x84, vga_text_height - 1);	                 /* rows on screen - 1 */
    pokeb(0x40, 0x85, font_height);		                     /* char height */

    /* Set white-on-black for all text. */
    for(size_t i = 0; i < vga_text_width * vga_text_height; i++) {
		pokeb(0xB800, i * 2 + 1, 7);
    }
}

void VGASetGraphicsMode(uint16_t width, uint16_t height, uint16_t depth) {
    //VGAWriteRegisters(vga_graphics_320x200x256_mode_x);
    //vga_graphics_width = 320;
    //vga_graphics_height = 200;
    //VGAGraphicsDrawPixel = VGAGraphicsDrawPixel8x;
    //VGAGraphicsDrawX();

    VGAWriteRegisters(vga_graphics_640x480x16);
	vga_graphics_width = 640;
	vga_graphics_height = 480;
	VGAGraphicsDrawPixel = VGAGraphicsDrawPixel4p;
	VGAGraphicsDrawX();
}

void VGAGraphicsDrawPixel1(uint8_t x, uint8_t y, uint8_t c) {

}

void VGAGraphicsDrawPixel2(uint8_t x, uint8_t y, uint8_t c) {

}

void VGAGraphicsDrawPixel4p(uint8_t x, uint8_t y, uint8_t c) {
    uint8_t width_in_bytes, offset, mask, pmask;

	width_in_bytes = vga_graphics_width / 8;
	offset = width_in_bytes * y + x / 8;
	x = (x & 7) * 1;
	mask = 0x80 >> x;
	pmask = 1;
	for(size_t p = 0; p < 4; p++) {
		VGASetPlane(p);
		if(pmask & c)
			vpokeb(offset, vpeekb(offset) | mask);
		else
			vpokeb(offset, vpeekb(offset) & ~mask);
		pmask <<= 1;
	}
}

void VGAGraphicsDrawPixel8(uint8_t x, uint8_t y, uint8_t c) {
    uint8_t width_in_bytes, offset;

    width_in_bytes = vga_graphics_width;
	offset = width_in_bytes * y + x;
	vpokeb(offset, c);
}

void VGAGraphicsDrawPixel8x(uint8_t x, uint8_t y, uint8_t c) {
    uint8_t width_in_bytes, offset;
    width_in_bytes = vga_graphics_width / 4;
	offset = width_in_bytes * y + x / 4;
	VGASetPlane(x & 3);
	vpokeb(offset, c);
}

void VGAGraphicsDrawX() {
	uint8_t x, y;
    /* Clear screen. */
	for(y = 0; y < vga_graphics_height; y++) {
		for(x = 0; x < vga_graphics_width; x++) {
			VGAGraphicsDrawPixel(x, y, 0);
        }
    }
    /* draw 2-color X */
	for(y = 0; y < vga_graphics_height; y++) {
		VGAGraphicsDrawPixel((vga_graphics_width - vga_graphics_height) / 2 + y, y, 1);
		VGAGraphicsDrawPixel((vga_graphics_height + vga_graphics_width) / 2 - y, y, 2);
	}
}

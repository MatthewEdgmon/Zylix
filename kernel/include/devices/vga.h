#ifndef __VGA_H__
#define __VGA_H__

#include <stddef.h>
#include <stdint.h>

#define VGA_AC_INDEX              0x3C0
#define VGA_AC_WRITE              0x3C0
#define VGA_AC_READ               0x3C1
#define VGA_MISC_WRITE            0x3C2
#define VGA_SEQ_INDEX             0x3C4
#define VGA_SEQ_DATA              0x3C5
#define	VGA_DAC_READ_INDEX        0x3C7
#define	VGA_DAC_WRITE_INDEX       0x3C8
#define	VGA_DAC_DATA              0x3C9
#define	VGA_MISC_READ             0x3CC
#define VGA_GC_INDEX              0x3CE
#define VGA_GC_DATA               0x3CF
#define VGA_CRTC_INDEX_MONO       0x3B4
#define VGA_CRTC_DATA_MONO        0x3B5
#define VGA_CRTC_INDEX            0x3D4
#define VGA_CRTC_DATA             0x3D5
#define VGA_INSTAT_READ           0x3DA

#define VGA_NUMBER_SEQ_REGISTERS  5
#define VGA_NUMBER_CRTC_REGISTERS 25
#define VGA_NUMBER_GC_REGISTERS   9
#define VGA_NUMBER_AC_REGISTERS   21
#define VGA_NUMBER_REGISTERS      (1 + VGA_NUMBER_SEQ_REGISTERS + VGA_NUMBER_CRTC_REGISTERS + \
								       VGA_NUMBER_GC_REGISTERS + VGA_NUMBER_AC_REGISTERS)

enum vga_color {
	COLOR_BLACK = 0,
	COLOR_BLUE = 1,
	COLOR_GREEN = 2,
	COLOR_CYAN = 3,
	COLOR_RED = 4,
	COLOR_MAGENTA = 5,
	COLOR_BROWN = 6,
	COLOR_LIGHT_GREY = 7,
	COLOR_DARK_GREY = 8,
	COLOR_LIGHT_BLUE = 9,
	COLOR_LIGHT_GREEN = 10,
	COLOR_LIGHT_CYAN = 11,
	COLOR_LIGHT_RED = 12,
	COLOR_LIGHT_MAGENTA = 13,
	COLOR_LIGHT_BROWN = 14,
	COLOR_WHITE = 15,
};

void VGAReadRegisters(uint16_t* registers);
void VGAWriteRegisters(uint16_t* registers);
void VGAWriteFont(uint8_t* buffer, uint8_t font_height);
uint16_t VGAGetFramebufferSegment();
uint16_t VGAGetTextModeWidth();
uint16_t VGAGetTextModeHeight();
uint16_t VGAGetGraphicsModeWidth();
uint16_t VGAGetGraphicsModeHeight();
void VGASetPlane(uint8_t plane);
void VGASetTextMode(uint8_t high_res);
void VGASetGraphicsMode();
/* Pixel plotting functions. */
void VGAGraphicsDrawPixel1(uint8_t x, uint8_t y, uint8_t c);
void VGAGraphicsDrawPixel2(uint8_t x, uint8_t y, uint8_t c);
void VGAGraphicsDrawPixel4p(uint8_t x, uint8_t y, uint8_t c);
void VGAGraphicsDrawPixel8(uint8_t x, uint8_t y, uint8_t c);
void VGAGraphicsDrawPixel8x(uint8_t x, uint8_t y, uint8_t c);
void VGAGraphicsDrawX();

void SetupVGA();

#endif /* __VGA_H__ */

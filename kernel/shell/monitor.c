/**
 * monitor.c - Built-in RAM monitor program.
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

#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include <arch/io.h>
#include <arch/interrupts.h>

#include <devices/ps2keyboard.h>

#include <menu/monitor.h>
#include <terminal.h>
#include <vga.h>

uint16_t* current_address = (uint16_t*) 0xB8000;

uint16_t* selected_address = (uint16_t*) 0xB8000;
uint16_t selected_value = 0;

int shift_pressed = 0;
int should_exit = 0;

int RAMMonitorHandler(registers_t* registers) {
    uint8_t keyboard_scan_code;

    /* We do not need to probe the status bit on an IRQ. */
    keyboard_scan_code = PS2ReadData();

    /* If bit 7 is set, key was just released. */
    if(keyboard_scan_code & 0x80) {
        /* Handle a shift release. */
        if(keyboard_scan_code == 42) {
            shift_pressed = 0;
        }
        if(keyboard_scan_code == 54) {
            shift_pressed = 0;
        }
    } else {
        /* Handle a shift press. */
        if(keyboard_scan_code == 42) {
            shift_pressed = 1;
        }
        if(keyboard_scan_code == 54) {
            shift_pressed = 1;
        }
        /* Up arrow. */
        if(keyboard_scan_code == 72) {
            selected_address--;
        }
        /* Down arrow. */
        if(keyboard_scan_code == 80) {
            selected_address++;
        }
        /* Left arrow. */
        if(keyboard_scan_code == 75) {
            selected_value--;
        }
        /* Right arrow. */
        if(keyboard_scan_code == 77) {
            selected_value++;
        }
        /* S key. */
        if(keyboard_scan_code == 31) {
            *current_address = selected_value;
        }
        /* Escape key. */
        if(keyboard_scan_code == 1) {
            should_exit = 1;
        }
    }

    TerminalClear();
    RAMMonitorUpdate();

    /* Send EOI */
    PICSendEOI(IRQ_KEYBOARD);

    return 1;
}

/**
 * No "main" here, built as a part of the kernel
 */
int RAMMonitorMain() {

    PICSetMask(IRQ_KEYBOARD);
    PICDisableInterrupts();
    PICUninstallIRQHandler(IRQ_KEYBOARD);
    PICInstallIRQHandler(IRQ_KEYBOARD, RAMMonitorHandler);
    PICResumeInterrupts();
    PICClearMask(IRQ_KEYBOARD);

    while(1) {

    }

    PICSetMask(IRQ_KEYBOARD);
    PICDisableInterrupts();
    PICUninstallIRQHandler(IRQ_KEYBOARD);
    PICInstallIRQHandler(IRQ_KEYBOARD, PS2KeyboardHandler);
    PICResumeInterrupts();
    PICClearMask(IRQ_KEYBOARD);

    return 0;
}

int RAMMonitorUpdate() {
    current_address = selected_address - 12;

    /* Display the lines above the selected address. */
    for(int i = 0; i < 11; i++) {
        current_address++;
        /* Print the address in blue. */
        TerminalSetColor(TerminalMakeColor(COLOR_LIGHT_BLUE, COLOR_BLACK));
        printf("0x%X: ", current_address);
        /* Print the data in white. */
        TerminalSetColor(TerminalMakeColor(COLOR_WHITE, COLOR_BLACK));
        printf("0x%X ", *current_address);
        /* And finally a newline. */
        printf("\n");
    }

    /* Display the selected address. */
    current_address++;
    /* Print the address in red. */
    TerminalSetColor(TerminalMakeColor(COLOR_LIGHT_RED, COLOR_BLACK));
    printf("0x%X: ", current_address);
    /* Print the data in white. */
    TerminalSetColor(TerminalMakeColor(COLOR_WHITE, COLOR_BLACK));
    printf("0x%X ", *current_address);
    /* And finally a newline. */
    printf("\n");

    /* Display the lines below the selected address. */
    for(int i = 0; i < 11; i++) {
        current_address++;
        /* Print the address in blue. */
        TerminalSetColor(TerminalMakeColor(COLOR_LIGHT_BLUE, COLOR_BLACK));
        printf("0x%X: ", current_address);
        /* Print the data in white. */
        TerminalSetColor(TerminalMakeColor(COLOR_WHITE, COLOR_BLACK));
        printf("0x%X ", *current_address);
        /* And finally a newline. */
        printf("\n");
    }

    /* The second to last line displays key commands. */
    printf("(S)et Value (Down)\\(Up) Change Address. (<)\\(>) Change Value. (Shift) x10\n");

    /* The bottom line displays selected values. */
    TerminalSetColor(TerminalMakeColor(COLOR_WHITE, COLOR_BLACK));
    printf("Selected Address:");
    TerminalSetColor(TerminalMakeColor(COLOR_LIGHT_RED, COLOR_BLACK));
    printf(" 0x%X ", selected_address);
    TerminalSetColor(TerminalMakeColor(COLOR_WHITE, COLOR_BLACK));
    printf("Selected Value:");
    TerminalSetColor(TerminalMakeColor(COLOR_LIGHT_GREEN, COLOR_BLACK));
    printf(" 0x%X ", selected_value);
    TerminalSetColor(TerminalMakeColor(COLOR_WHITE, COLOR_BLACK));

    return 0;
}

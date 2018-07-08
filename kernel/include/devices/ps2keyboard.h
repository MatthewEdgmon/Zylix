/**
 * ps2keyboard.h - Setup and handling of PS/2 keyboards.
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

#ifndef __PS2KEYBOARD_H__
#define __PS2KEYBOARD_H__

#include <stdbool.h>
#include <stdint.h>

#include <arch/interrupts.h>

#include <devices/ps2.h>

/* PS/2 Data port keyboard commands. */
/* NOTE: Send through the PS/2 Data port (0x60). */
#define PS2_KEYBOARD_SET_LEDS            0xED    /* Sets the LEDs on the keyboard, state is sent by next data byte. */
#define PS2_KEYBOARD_ECHO                0xEE    /* Echo (for diagnostic purposes, and useful for device removal detection). */
#define PS2_KEYBOARD_GET_SET_SCANCORE    0xF0    /* Gets or sets the current scan code set. */
#define PS2_KEYBOARD_IDENTIFY            0xF2    /* Identify keyboard, responds with 0xFA and none or more ID bytes. */
#define PS2_KEYBOARD_SET_TYPEMATIC       0xF3    /* Set the typematic rate and delay. */
#define PS2_KEYBOARD_ENABLE_SCANNING     0xF4
#define PS2_KEYBOARD_DISABLE_SCANNING    0xF5
#define PS2_KEYBOARD_SET_DEFAULTS        0xF6
#define PS2_KEYBOARD_SET_ALL_TYPEMATIC   0xF7
#define PS2_KEYBOARD_SCANCODE_FOR_KEY    0xFD    /* Set specific key to make only. */
#define PS2_KEYBOARD_RESEND              0xFE    /* Resend last byte. */
#define PS2_KEYBOARD_RESET_SELF_TEST     0xFF    /* Reset and start self test. */

/* PS/2 Keyboard special response bytes. */
/* NOTE: All other response bytes are scan codes. */
#define PS2_KEYBOARD_RESPONSE_ERROR1     0x00    /* Key detection error or internal buffer overrun. */
#define PS2_KEYBOARD_RESPONSE_TEST_PASS  0xAA    /* Self test passed. */
#define PS2_KEYBOARD_RESPONSE_ECHO       0xEE    /* Response to echo command. */
#define PS2_KEYBOARD_RESPONSE_ACK        0xFA    /* Command acknowledged. */
#define PS2_KEYBOARD_RESPONSE_TEST_FAIL1 0xFC    /* Self test failed. */
#define PS2_KEYBOARD_RESPONSE_TEST_FAIL2 0xFD    /* Self test failed. */
#define PS2_KEYBOARD_RESPONSE_RESEND     0xFE    /* Resend last command. */
#define PS2_KEYBOARD_RESPONSE_ERROR2     0xFF    /* Key detection error or internal buffer overrun. */

typedef struct {
    /* If the keyboard physically exists, non-zero. */
    bool available;
    /* Which PS/2 port this keyboard is plugged into. */
    uint8_t ps2_port;

    uint8_t scan_code;

} keyboard_state_t;

void PS2KeyboardSetLED(uint8_t caps_lock, uint8_t num_lock, uint8_t scroll_lock);
uint8_t PS2KeyboardGetKey();
uint8_t PS2KeyboardGetExtendedKey();
void SetupPS2Keyboard();

int PS2KeyboardHandler(registers_t* registers);

#endif /* __PS2KEYBOARD_H__ */

/**
 * ps2keyboard.c - PS/2 keybaord routines and interrupt handler.
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

#include <ctype.h>
#include <stdint.h>
#include <stdio.h>

#include <arch/io.h>
#include <arch/interrupts.h>
#include <arch/registers.h>

#include <devices/ps2.h>
#include <devices/ps2keyboard.h>

#include <shell/shell.h>

// Uncomment this to see how a keypress corresponds to it's character.
//#define DEBUG_SCANCODES

#define INPUT_ARRAY_LENGTH 256
int input_array_index = 0;
char input_array[INPUT_ARRAY_LENGTH];

uint8_t number_lock_state = 0;
uint8_t caps_lock_state = 0;
uint8_t scroll_lock_state = 0;

uint8_t left_shift_state = 0;
uint8_t right_shift_state = 0;
uint8_t left_control_state = 0;
uint8_t right_control_state = 0;
uint8_t left_alt_state = 0;
uint8_t right_alt_state = 0;

uint8_t current_key = 0;
uint8_t current_extended_key = 0;

uint8_t current_key_held = 0;

uint16_t US_QWERTY_1[128] = {
0,                 /* Escape */
'1','2','3','4','5','6','7','8','9','0',
  '-','=',
'\b', '\t',        /* Backspace and tab. */
'q','w','e','r','t','y','u','i','o','p',
'[',']',
'\n',              /* Enter */
128,               /* Left Control */
'a','s','d','f','g','h','j','k','l',
';','\'','`',
127,//Left Shift
'\\',
'z','x','c','v','b','n','m',',','.',
'/',
127,//Right Shift
'*',
129,//Left Alt
' ',//Spacebar
0,//Capslock
0,0,0,0,0,0,0,0,0,0,//F1 to F10
0,//Number Lock
0,//Scroll Lock

//Number Pad with Number Lock:

'7',//Home
'8',//Up Arrow
'9',//Page Up
'-',//Number Pad Minus
'4',//Left Arrow
'5',//Number Pad 5
'6',//Right Arrow
'+',//Number Pad Plus
'1',//End
'2',//Down Arrow
'3',//Page Down
'0',//Insert
'.',//Delete
0, 0, 0,//Absolutely Nothing
0, 0, // F11 and F12

0
};

uint16_t US_QWERTY_sh[128]= {

  // Key Presses

  0,//Escape
  '!','@','#','$','%','^','&','*','(',')',
  '_','+',
  '\b','\t',//Backspace and Tab
  'Q','W','E','R','T','Y','U','I','O','P',
  '{','}',
  '\n',//Enter
  128,//Left Control
  'A','S','D','F','G','H','J','K','L',
  ':','\"','~',
  127,//Left Shift
  '|',
  'Z','X','C','V','B','N','M','<','>',
  '?',
  127,//Right Shift
  '*',
  129,//Left Alt
  ' ',//Spacebar
  0,//Capslock
  0,0,0,0,0,0,0,0,0,0,//F1 to F10
  0,//Number Lock
  0,//Scroll Lock

  //Number Pad with Number Lock:

  '7',//Home
  '8',//Up Arrow
  '9',//Page Up
  '-',//Number Pad Minus
  '4',//Left Arrow
  '5',//Number Pad 5
  '6',//Right Arrow
  '+',//Number Pad Plus
  '1',//End
  '2',//Down Arrow
  '3',//Page Down
  '0',//Insert
  '.',//Delete
  0,0,0,//Absolutely Nothing
  0,0,// F11 and F12

  // Key Presses End
  0     // That's all

  };

uint16_t US_QWERTY_extended[]= {
'\n',         /* Keypad Enter */
0,            //Right Control */
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0,//Print Screen 1 */
0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
'/',0,
0,//Print Screen 2 */
0,//Right Alt */
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* Home */
0,//Cursor Up */
0,//Page Up */
0,0,//Left */
0,0,//Right */
0,0,//End */
0,//Down */
0,//Page Down
0,//Insert
0,//Delete
0,0,0,0,0,0,0,
0,//Left GUI
0,//Right GUI
0,//Apps

};

void PS2KeyboardSetLED(uint8_t caps_lock, uint8_t num_lock, uint8_t scroll_lock) {
    uint8_t response_byte = 0x00;
    uint8_t byte_to_send = 0x00;
    uint8_t byte = 0x00;

    if(scroll_lock) {
        scroll_lock_state = 1;
        byte_to_send = byte ^ 0x01;
        byte = byte_to_send;
    } else {
        scroll_lock_state = 0;
    }

    if(num_lock) {
        number_lock_state = 1;
        byte_to_send = byte ^ 0x02;
        byte = byte_to_send;
    } else {
        number_lock_state = 0;
    }

    if(caps_lock) {
        caps_lock_state = 1;
        byte_to_send = byte ^ 0x04;
        byte = byte_to_send;
    } else {
        caps_lock_state = 0;
    }

    /* Send the command. */
    PS2WaitInputBuffer();
    PS2SendData(PS2_KEYBOARD_SET_LEDS);

    PS2WaitOutputBuffer();
    response_byte = PS2ReadData();

    /* Send the status byte. */
    PS2WaitInputBuffer();
    PS2SendData(byte_to_send);
}

uint8_t PS2KeyboardGetKey() {
    return current_key;
}

uint8_t PS2KeyboardGetExtendedKey() {
    return current_extended_key;
}

int PS2KeyboardHandler(cpu_registers_t* registers) {
    uint8_t keyboard_scan_code;

    /* We do not need to probe the status bit on an IRQ. */
    keyboard_scan_code = PS2ReadData();

    /* If bit 7 is set, key was just released. */
    if(keyboard_scan_code & 0x80) {
        /* Handle a shift release. */
        if(US_QWERTY_1[(keyboard_scan_code ^ 0x80) - 1] == 127) {
            left_shift_state = 0;
            right_shift_state = 0;
        }
        /* Handle a control release. */
        if(US_QWERTY_1[(keyboard_scan_code ^ 0x80) - 1] == 128) {
            left_control_state = 0;
            right_control_state = 0;
        }
        /* Handle an alt release. */
        if(US_QWERTY_1[(keyboard_scan_code ^ 0x80) - 1] == 129) {
            left_alt_state = 0;
            right_alt_state = 0;
        }
        /* Handle a keypad release. */
        if(keyboard_scan_code == 0xE0) {
            PS2WaitOutputBuffer();
            keyboard_scan_code = PS2ReadData();
        }
        /* Handle a Pause/Break keypress. */
        if(keyboard_scan_code == 0xE1) {
            PS2WaitOutputBuffer();
            keyboard_scan_code = PS2ReadData();
            PS2WaitOutputBuffer();
            keyboard_scan_code = PS2ReadData();
            PS2WaitOutputBuffer();
            keyboard_scan_code = PS2ReadData();
            PS2WaitOutputBuffer();
            keyboard_scan_code = PS2ReadData();
            PS2WaitOutputBuffer();
            keyboard_scan_code = PS2ReadData();
        }
    } else {
        /* Handle a shift press. */
        if(US_QWERTY_1[keyboard_scan_code - 1] == 127) {
            left_shift_state = 1;
            right_shift_state = 1;
        }
        /* Handle a control press. */
        if(US_QWERTY_1[keyboard_scan_code - 1] == 128) {
            left_control_state = 1;
            right_control_state = 1;
        }
        /* Handle an alt press. */
        if(US_QWERTY_1[keyboard_scan_code - 1] == 129) {
            left_alt_state = 1;
            right_alt_state = 1;
        }
        /* Handle an escape press. */
        if(keyboard_scan_code == 1) {
            current_key = 0xFF;
            current_extended_key = 0x99;
        }
        /* Handle a newline code. */
        if(US_QWERTY_1[keyboard_scan_code - 1] == '\n') {
            current_key = '\n';
        }

        /* Handle space. */
        if(keyboard_scan_code == 57) {
            printf(" ");
            input_array_index++;
            input_array[input_array_index] = ' ';
        }

        /* Handle backspace. */
        if(keyboard_scan_code == 14) {
            if(input_array_index > 0) {
                printf("\b");
                input_array[input_array_index] = '\0';
                input_array_index--;
            }
        }

        /* Handle return. */
        if(keyboard_scan_code == 28) {
            printf("\n");

            /* Execute. */
            Shell(input_array);

            /* Empty out the buffer. */
            input_array_index = 0;
            for(int i = 0; i < INPUT_ARRAY_LENGTH; i++) {
                input_array[i] = '\0';
            }
        }

        if(isprint(US_QWERTY_1[(keyboard_scan_code) - 1]) && isprint(US_QWERTY_1[(keyboard_scan_code) - 1])) {
            if(left_shift_state || right_shift_state || caps_lock_state) {
                current_key = US_QWERTY_sh[(keyboard_scan_code) - 1];
            } else {
                current_key = US_QWERTY_1[(keyboard_scan_code) - 1];
            }

            printf("%c", current_key);
            input_array[input_array_index] = current_key;
            input_array_index++;
        }

#ifdef DEBUG_SCANCODES
        printf("[%c is %d] ", keyboard_scan_code, keyboard_scan_code);
#endif

    }

    /* Send EOI */
    PICSendEOI(IRQ_KEYBOARD);

    return 1;
}

void SetupPS2Keyboard() {
    uint8_t response_byte;

    /* Disable interrupts. */
    PICSetMask(IRQ_KEYBOARD);
    PICDisableInterrupts();

    /* Disable scanning. */
    PS2WaitInputBuffer();
    PS2SendData(PS2_KEYBOARD_DISABLE_SCANNING);

    PS2WaitOutputBuffer();
    response_byte = PS2ReadData();

    /* Identify device. */
    PS2WaitInputBuffer();
    PS2SendData(PS2_KEYBOARD_IDENTIFY);

    PS2WaitOutputBuffer();
    response_byte = PS2ReadData();

    if(response_byte == 0xFA) {
        uint8_t identify_byte;

        PS2WaitOutputBuffer();
        identify_byte = PS2ReadData();

        switch(identify_byte) {
            /* Standard PS/2 mouse. */
            case 0x00:
                printf("Device in PS/2 port 1 is a standard PS/2 mouse.\n");
                break;
            /* Scroll mouse. */
            case 0x03:
                printf("Device in PS/2 port 1 is a mouse with scroll wheel.\n");
                break;
            /* 5-button mouse. */
            case 0x04:
                printf("Device in PS/2 port 1 is a 5-button mouse.\n");
                break;
            /* MF2 keyboard. */
            case 0xAB:
                PS2WaitOutputBuffer();
                identify_byte = PS2ReadData();
                switch(identify_byte) {
                    case 0x41:
                    case 0xC1:
                        printf("Device in PS/2 port 1 is an MF2 keyboard with translation.\n");
                        break;
                    case 0x83:
                        printf("Device in PS/2 port 1 is an MF2 keyboard.\n");
                        break;
                    default:
                        printf("Unknown device type in PS/2 port 1: 0x%X\n", response_byte);
                }
                break;
            default:
                printf("Unknown device type in PS/2 port 1: 0x%X\n", response_byte);
                break;
        }

    }

    /* Perform self-test. */
    SelfTest:
    PS2WaitInputBuffer();
    PS2SendData(PS2_KEYBOARD_RESET_SELF_TEST);

    PS2WaitOutputBuffer();
    response_byte = PS2ReadData();

    switch(response_byte) {
        case PS2_KEYBOARD_RESPONSE_TEST_PASS:
            printf("PS/2 keyboard self-test passed.\n");
            break;
        case PS2_KEYBOARD_RESPONSE_ACK:
            printf("PS/2 keyboard unexpected ACK.\n");
            break;
        case PS2_KEYBOARD_RESPONSE_TEST_FAIL1:
            printf("PS/2 keyboard self-test failed.\n");
            break;
        case PS2_KEYBOARD_RESPONSE_TEST_FAIL2:
            printf("PS/2 keyboard self-test failed.\n");
            break;
        case PS2_KEYBOARD_RESPONSE_RESEND:
            printf("PS/2 keyboard requests resend.\n");
            goto SelfTest;
            break;
        default:
            printf("PS/2 keyboard self-test failed with unknown response: 0x%X\n", response_byte);
            break;
    }

    /* Change scan code set to 1. */
    PS2WaitInputBuffer();

    /* Set typematic info. */
    PS2WaitInputBuffer();
    PS2SendData(PS2_KEYBOARD_SET_TYPEMATIC);

    PS2WaitInputBuffer();
    PS2SendData(0x23);

    /* Enable scanning. */
    PS2WaitInputBuffer();
    PS2SendData(PS2_KEYBOARD_ENABLE_SCANNING);

    /* Set num-lock on. */
    PS2KeyboardSetLED(0, 1, 0);

    /* Setup the IRQ handler. */
    PICInstallIRQHandler(IRQ_KEYBOARD, PS2KeyboardHandler);

    /* And finally re-enable interrupts. */
    PICResumeInterrupts();
    PICClearMask(IRQ_KEYBOARD);
}

#include <arch/IO.h>

#include <devices/ps2.h>
#include <devices/ps2keyboard.h>

#include <common.h>
#include <libc/stdint.h>
#include <terminal.h>

uint8_t number_lock_state = 0;
uint8_t caps_lock_state = 0;
uint8_t scroll_lock_state = 0;

uint8_t left_shift_state = 0;
uint8_t right_shift_state = 0;
uint8_t left_control_state = 0;
uint8_t right_control_state = 0;
uint8_t left_alt_state = 0;
uint8_t right_alt_state = 0;

char US_QWERTY_1[128] = {
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

int PS2KeyboardSelfTest() {
    uint8_t response;

    PS2WaitInputBuffer();
    PS2SendData(PS2_KEYBOARD_RESET_SELF_TEST);

    response = inb(0x60);

    switch(response) {
        case 0xAA:
            /* Self test passed. */
            TerminalPrintString("Self-test passed.");
            return 0;
        case 0xFA:
            TerminalPrintString("Unexpected ACK.");
            return 1;
        case 0xFC:
            TerminalPrintString("Self-test failed.");
            return 2;
        case 0xFD:
            TerminalPrintString("Self-test failed.");
            return 3;
        case 0xFE:
            TerminalPrintString("Resend requested.");
            return 4;
        default:
            TerminalPrintString("Got unknown Keyboard response.");
            return -1;
    }
    return 0;
}

void PS2KeyboardEnableScanning() {
    uint8_t response;
    outb(0x64, 0xF5);
    io_wait();
    response = inb(0x60);

    if(response == 0xFA) {
        TerminalPrintString("KeyboardEnableScanning() got an ACK");
    }

    if(response == 0xFE) {
        TerminalPrintString("KeyboardEnableScanning() got a resend request.");
    }

}

void PS2KeyboardDisableScanning() {
    uint8_t response;
    outb(0x64, 0xF5);
    io_wait();
    response = inb(0x60);
}

void PS2KeyboardSetLED(uint8_t caps_lock, uint8_t num_lock, uint8_t scroll_lock) {
    
}

void SetupPS2Keyboard() {

    /* Disable scanning. */
    PS2KeyboardDisableScanning();

    /* Perform self-test. */
    PS2KeyboardSelfTest();

    /* Change scan code set to 1. */

    /* Set typematic info. */

    /* Enable scanning. */
    PS2KeyboardEnableScanning();

    /* Set num-lock on. */
    PS2KeyboardSetLED(0, 1, 0);
}

/* Handler for IRQ1 */
void PS2KeyboardHandler() {
    uint8_t keyboard_scan_code;

    keyboard_scan_code = PS2ReadData();

    /* If bit 7 is set, key was just released. */
    if(keyboard_scan_code & 0x80) {

    }

}
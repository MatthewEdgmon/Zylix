#include <devices/ps2.h>
#include <devices/ps2keyboard.h>
#include <devices/ps2mouse.h>

#include <arch/IO.h>
#include <common.h>
#include <libc/stdbool.h>
#include <libc/stdint.h>
#include <terminal.h>

#define PS2_KEYBOARD_DATA_PORT 0x60
#define PS2_KEYBOARD_COMMAND_PORT 0x64

/**
 * 0x20 and 0x21 Control/mask ports of the master PIC
 * 0xA0 and 0xA1 Control/mask ports of the slave PIC
 * 0x60 Data port from PS2 controller.
 * 0x64 Command port from PS2 controller.
 */

 /**
  * Keyboard Commands:
  *
  * Set LEDs:
  *		Command - 0xED
  *		Data	- 0x00 Scroll Lock
  *				- 0x01 Number Lock
  *				- 0x02 Caps Lock
  *
  *		Returns	- 0xFA ACK
  *				- 0xFE Resend
  *		
  *	Echo:
  *		Command - 0xEE
  *		Data	- N/A
  *
  *		Returns	- 0xEE Echo
  *				- 0xFE Resend
  *
  * Get/Set scan code set:
  *		Command - 0xF0
  *		Data	- 0x
  *
  * Enable scanning:
  *		Command - 0xF4
  *		Data	- N/A
  *
  *		Returns - 0xFA ACK
  *				- 0xFE Resend
  *
  * Disable scanning:
  *		Command - 0xF5
  *		Data	- N/A
  *
  *		Returns - 0xFA ACK
  *				- 0xFE Resend
  *
  * Resend last byte:
  *		Command - 0xFE
  *		Data	- 0x00
  *
  * Self test:
  *		Command - 0xFF
  *		Data	- N/A
  *
  *		Returns	- 0xAA Self test passed
  *				- 0xFC Self test failed
  *				- 0xFD Self test failed
  *				- 0xFE Resend
  */

/**
 * How to identify:
 *
 * Send 0xF5 - Disable scanning.
 * Get 0xFA or 0xFE
 * Send 0xF2 - Identify
 * Get 0xFA or 0xFE
 * Get 0x00 	Standard PS/2 mouse
 *	0x03 	Mouse with scroll wheel
 *	0x04 	5-button mouse
 *	0xAB, 0x41 or 0xAB, 0xC1 	MF2 keyboard with translation enabled in the PS/Controller (not possible for the second PS/2 port)
 *	0xAB, 0x83 	MF2 keyboard
 * Wait to see if two bytes.
 * Send 0xF4 - Enable scanning.
 * Get 0xFA or 0xFE
*/

/* We assume the first device is a keyboard, and the second is a mouse. */
uint8_t ps2_device1_type = 0x00;
uint8_t ps2_device2_type = 0x00;

bool ps2_controller_present = 0;
bool ps2_has_first_channel = 0;
bool ps2_has_second_channel = 0;

void PS2SendData(uint8_t data) {
    outb(PS2_DATA_PORT, data);
}

uint8_t PS2ReadData() {
    uint8_t response;
    response = inb(PS2_DATA_PORT);
    return response;
}

void PS2SendCommand(uint8_t command) {
    outb(PS2_COMMAND_REGISTER, command);
}

uint8_t PS2ReadStatus() {
    uint8_t response;
    response = inb(PS2_STATUS_REGISTER);
    return response;
}

void PS2WaitOutputBuffer() {
    uint8_t response;
    for(;;) {
        response = PS2ReadStatus();
        /* Check if the output buffer flag is set. */
        if(BIT_CHECK(PS2ReadStatus(), 0)) {
            break;
        }
    }
}

void PS2WaitInputBuffer() {
    uint8_t response;
    for(;;) {
        response = PS2ReadStatus();
        /* Check if the input buffer flag is clear. */
        if(!BIT_CHECK(PS2ReadStatus(), 1)) {
            break;
        }
    }
}

/**
 * We rely on our bootloader setting the A20, but we have code for it just in case.
 */
void PS2EnableA20() {
    char response_byte;

    /* Disable both PS/2 ports. */
    PS2WaitInputBuffer();
    PS2SendCommand(PS2_COMMAND_DISABLE_PORT1);

    PS2WaitInputBuffer();
    PS2SendCommand(PS2_COMMAND_DISABLE_PORT2);

    /* Tell the PS/2 controller to send us the config. */
    PS2WaitInputBuffer();
    PS2SendCommand(PS2_COMMAND_READ_CONFIG);

    /* Get the status byte. */
    response_byte = PS2ReadStatus();

    /* Check if the A20 bit is set. */
    if((response_byte & 0x02) != 0x02) {
        /* A20 is NOT set. Set it and write it. */
        PS2SendCommand(PS2_COMMAND_WRITE_CONFIG);
        PS2SendCommand(response_byte | 0x02);
        TerminalPrintString("A20 line set.\n");
    } else {
        /* A20 was set. */
        TerminalPrintString("A20 line was already set.\n");
    }
    
    /* Re-enable both ports. */
    PS2WaitInputBuffer();
    PS2SendCommand(PS2_COMMAND_ENABLE_PORT1);

    PS2WaitInputBuffer();
    PS2SendCommand(PS2_COMMAND_ENABLE_PORT2);

    return;
}

void SetupPS2() {
    char response_byte;

    /* Initialize USB controllers. */
    /* Determine if PS2 exists. */

    /* Disable devices so they don't send data. */
    PS2WaitInputBuffer();
    PS2SendCommand(PS2_COMMAND_DISABLE_PORT1);

    PS2WaitInputBuffer();
    PS2SendCommand(PS2_COMMAND_DISABLE_PORT2);

    /* Flush output buffer. */
    PS2ReadStatus();

    /* Set the controller configuration byte. */
    response_byte = PS2ReadStatus();

    /* Perform controller self test. */
    PS2WaitInputBuffer();
    PS2SendCommand(PS2_COMMAND_TEST_CONTROLLER);

    PS2WaitOutputBuffer();
    if(PS2ReadData() == PS2_RESPONSE_TEST_PASS) {
        TerminalPrintString("PS2 controller passed self test.\n");
    } else {
        TerminalPrintString("PS2 controller did not pass self test.\n");
    }

    /* Determine if there is 2 channels. */
    PS2WaitInputBuffer();
    PS2SendCommand(PS2_COMMAND_ENABLE_PORT2);

    PS2WaitInputBuffer();
    PS2SendCommand(PS2_COMMAND_READ_CONFIG);

    response_byte = PS2ReadStatus();

    /* Check if bit 5 of the controller config is set. */
    if(BIT_CHECK(response_byte, 5)) {
        TerminalPrintString("PS/2 controller has no second channel.\n");
        ps2_has_second_channel = false;
    } else {
        TerminalPrintString("PS/2 controller has a second channel.\n");
        ps2_has_second_channel = true;
    }

    /* Disable port 2 again to finish startup. */
    PS2WaitInputBuffer();
    PS2SendCommand(PS2_COMMAND_DISABLE_PORT2);

    /* Perform interface tests. */

    /* Finally re-enable the devices. */
    PS2WaitInputBuffer();
    PS2SendCommand(PS2_COMMAND_ENABLE_PORT1);

    PS2WaitInputBuffer();
    PS2SendCommand(PS2_COMMAND_ENABLE_PORT2);

    /* Reset device 1. */
    PS2WaitInputBuffer();
    PS2SendCommand(PS2_KEYBOARD_RESET_SELF_TEST);

    /* Reset device 2. */
    PS2WaitInputBuffer();
    PS2SendCommand(PS2_COMMAND_WRITE_PORT2_INPUT);
}

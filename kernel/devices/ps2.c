#include <devices/ps2.h>

#include <arch/IO.h>

#include <common.h>
#include <types.h>

#include <terminal.h>

#define PS2_KEYBOARD_DATA_PORT 0x60
#define PS2_KEYBOARD_COMMAND_PORT 0x64

/**
 * 0x20 and 0x21 Control/mask ports of the master PIC
 * 0xA0 and 0xA1 Control/mask ports of the slave PIC
 * 0x60 Data port from PS2 controller.
 * 0x64 Command port from PS2 controller.
 */

/* IO test code to reset the CPU, regardless of state. */
// outb(0x64, 0xFE);

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

uint8_t ps2_controller_present = 0;
uint8_t ps2_has_first_channel = 0;
uint8_t ps2_has_second_channel = 0;

void PS2SendData(uint8_t data) {
    while(BIT_CHECK(PS2ReadStatus(), 1)) {
            io_wait();
    }
    outb(0x60, data);
}

uint8_t PS2ReadData() {
    uint8_t response;
    wait:
    if(BIT_CHECK(PS2ReadStatus(), 0)) {
        response = inb(0x60);
        return response;
    } else {
        goto wait;
    }
    return 0;
}

void PS2SendCommand(uint8_t command) {
    while(BIT_CHECK(PS2ReadStatus(), 1)) {
            io_wait();
    }
    outb(0x64, command);
}

uint8_t PS2ReadStatus() {
    uint8_t response;
    response = inb(0x64);
    return response;
}

void PS2DisableDevices() {
    /* Disable first channel. */
    PS2SendCommand(0xAD);
    /* Disable second channel. */
    PS2SendCommand(0xA7);
}

void PS2EnableDevices() {
    /* Enable first channel. */
    PS2SendCommand(0xAE);
    /* Enable second channel. */
    PS2SendCommand(0xA8);
}

void PS2TestDevices() {

}

void PS2CheckSecondChannel() {
    /* Enable second channel. */
    PS2SendCommand(0xA8);
    /* Tell controller to check Controller Configuration Byte. */
    PS2SendCommand(0x20);
    /* Wait for response. */
    io_wait();
}

/* The PS2 controller ties the CPU reset pin high. */
void PS2PulseReset() {
    PS2SendCommand(0xFE);
    HALT();
}

void SetupPS2() {
    /* Initialize USB controllers. */
    /* Determine if PS2 exists. */

    /* Disable devices so they don't send data. */
    PS2DisableDevices();

    /* Flush output buffer. */
    /* Set the controller configuration byte. */

    /* Perform controller self test. */
    PS2SendCommand(0xAA);

    if(PS2ReadData() != 0x55) {
        TerminalPrintString("PS2 controller did not pass self test.\n");
    }

    /* Determine if there is 2 channels. */
    /* Perform interface tests. */

    /* Finally re-enable the devices. */
    PS2EnableDevices();

    /* Reset devices. */
}

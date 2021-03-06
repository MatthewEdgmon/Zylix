/**
 * ps2.c - Setup and handling of IBM PS/2 devices (keyboard/mouse).
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

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include <arch/io.h>
#include <arch/interrupts.h>
#include <arch/registers.h>

#include <devices/ps2.h>
#include <devices/ps2keyboard.h>
#include <devices/ps2mouse.h>

#include <common.h>

/* We assume the first device is a keyboard, and the second is a mouse. */
uint8_t ps2_device1_type = 0x00;
uint8_t ps2_device2_type = 0x00;

/* Do we actually have a PS/2 controller? */
bool ps2_controller_present = 0;
/* Which PS/2 channels are present? */
bool ps2_has_first_channel = 0;
bool ps2_has_second_channel = 0;
/* Which ports have something plugged in? */
bool ps2_first_channel_active = 0;
bool ps2_second_channel_active = 0;

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
    for(;;) {
        /* Check if the input buffer flag is clear. */
        if(!BIT_CHECK(PS2ReadStatus(), 1)) {
            break;
        }
    }
}

/**
 * We rely on our bootloader setting the A20, but we have code for it just in case.
 */
void SetupA20() {
    uint8_t response_byte;

    /* Do a couple of dummy writes to clear the output buffers. */
    PS2ReadData();
    PS2ReadData();

    /* Disable interrupts. */
    PICDisableInterrupts();

    /* Disable both PS/2 ports. */
    PS2WaitInputBuffer();
    PS2SendCommand(PS2_COMMAND_DISABLE_PORT1);

    PS2WaitInputBuffer();
    PS2SendCommand(PS2_COMMAND_DISABLE_PORT2);

    A20_check:

    /* Tell the PS/2 controller to send us the config. */
    PS2WaitInputBuffer();
    PS2SendCommand(PS2_COMMAND_READ_CONFIG);

    /* Get the status byte. */
    response_byte = PS2ReadData();

    /* Check if the A20 bit is set. */
    if((response_byte & 0x02) != 0x02) {
        /* A20 is NOT set. Set it and write it. */
        PS2WaitOutputBuffer();
        PS2SendCommand(PS2_COMMAND_WRITE_CONFIG);
        PS2WaitOutputBuffer();
        PS2SendData(response_byte | 0x02);
        goto A20_check;
    } else {
        /* A20 was set. */
        printf("PS/2 A20 line set.\n");
    }

    /* Re-enable both ports. */
    PS2WaitInputBuffer();
    PS2SendCommand(PS2_COMMAND_ENABLE_PORT1);

    PS2WaitInputBuffer();
    PS2SendCommand(PS2_COMMAND_ENABLE_PORT2);

    /* And finally re-enable interrupts. */
    PICResumeInterrupts();

    return;
}

void SetupPS2() {
    char response_byte;

    /* Do a couple of dummy writes to clear the output buffers. */
    PS2ReadData();
    PS2ReadData();

    /* Initialize USB controllers. */
    /* Determine if PS2 exists using ACPI. */

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
        printf("PS/2 controller passed self test.\n");
    } else {
        printf("PS/2 controller did not pass self test.\n");
    }

    /* Determine if there is 2 channels. */
    PS2WaitInputBuffer();
    PS2SendCommand(PS2_COMMAND_ENABLE_PORT2);

    PS2WaitInputBuffer();
    PS2SendCommand(PS2_COMMAND_READ_CONFIG);

    response_byte = PS2ReadData();

    /* Check if bit 5 of the controller config is set. */
    if(BIT_CHECK(response_byte, 5)) {
        printf("PS/2 controller has no second channel.\n");
        ps2_has_second_channel = false;
    } else {
        printf("PS/2 controller has a second channel.\n");
        ps2_has_second_channel = true;
    }

    /* Disable port 2 again to finish startup. */
    PS2WaitInputBuffer();
    PS2SendCommand(PS2_COMMAND_DISABLE_PORT2);

    /* Test port 1. */
    PS2WaitInputBuffer();
    PS2SendCommand(PS2_COMMAND_TEST_PORT1);

    PS2WaitOutputBuffer();
    response_byte = PS2ReadData();

    switch(response_byte) {
        case PS2_RESPONSE_PORT_TEST_PASS:
            printf("PS/2 port 1 has passed self-test.\n");
            break;
        case PS2_RESPONSE_CLOCK_STUCK_LOW:
            printf("PS/2 port 1 has stuck low clock.\n");
            break;
        case PS2_RESPONSE_CLOCK_STUCK_HIGH:
            printf("PS/2 port 1 has stuck high clock.\n");
            break;
        case PS2_RESPONSE_DATA_STUCK_LOW:
            printf("PS/2 port 1 has stuck low data line.\n");
            break;
        case PS2_RESPONSE_DATA_STUCK_HIGH:
            printf("PS/2 port 1 has stuck high data line.\n");
            break;
        default:
            printf("PS/2 port 1 has failed self-test.\n");
            break;
    }

    /* Test port 2. */
    PS2WaitInputBuffer();
    PS2SendCommand(PS2_COMMAND_TEST_PORT2);

    PS2WaitOutputBuffer();
    response_byte = PS2ReadData();

    switch(response_byte) {
        case PS2_RESPONSE_PORT_TEST_PASS:
            printf("PS/2 port 2 has passed self-test.\n");
            break;
        case PS2_RESPONSE_CLOCK_STUCK_LOW:
            printf("PS/2 port 2 has stuck low clock.\n");
            break;
        case PS2_RESPONSE_CLOCK_STUCK_HIGH:
            printf("PS/2 port 2 has stuck high clock.\n");
            break;
        case PS2_RESPONSE_DATA_STUCK_LOW:
            printf("PS/2 port 2 has stuck low data line.\n");
            break;
        case PS2_RESPONSE_DATA_STUCK_HIGH:
            printf("PS/2 port 2 has stuck high data line.\n");
            break;
        default:
            printf("PS/2 port 2 has failed self-test.\n");
            break;
    }

    /* Re-enable device 1. */
    PS2WaitInputBuffer();
    PS2SendCommand(PS2_COMMAND_ENABLE_PORT1);

    /* Re-enable device 2. */
    PS2WaitInputBuffer();
    PS2SendCommand(PS2_COMMAND_ENABLE_PORT2);

    /* Identify device 1. */

    /* Identify device 2. */

}

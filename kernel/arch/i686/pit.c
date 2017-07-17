/**
 * pit.c - i686 Programmable Interval Timer
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

#include <stdio.h>

#include <arch/interrupts.h>
#include <arch/registers.h>
#include <arch/io.h>

#include "pic.h"

#define PIT_CHANNEL_0_DATA   0x40      /* Read/Write */
#define PIT_CHANNEL_1_DATA   0x41      /* Read/Write */
#define PIT_CHANNEL_2_DATA   0x42      /* Read/Write */
#define PIT_CHANNEL_COMMAND  0x43      /* Write only, read ignored. */

#define PIT_COMMAND_SET		 0x36

/* We use this value to set the timer to an exact amount of Hz */
#define PIT_SCALE 			 1193180
#define PIT_MASK			 0xFF

static uint64_t tick = 0;

/* Plays a sound on the PC speaker with the setup frequency. */
void PITSpeakerPlaySound() {
	uint8_t temp = inb(0x61);
    if(temp != (temp | 3)) {
        outb(0x61, temp | 3);
    }
}

/* Setup the PIT with a specific frequency in Hz. */
void PITSetupTimer(uint32_t frequency) {

	uint32_t divisor = PIT_SCALE / frequency;

	/* Send the command byte. */
	outb(PIT_CHANNEL_COMMAND, PIT_COMMAND_SET);

	uint8_t frequency_lower = (uint8_t)(divisor & PIT_MASK);
	uint8_t frequency_higher = (uint8_t)((divisor >> 8) & PIT_MASK);

	/* Send the frequency divisor. */
	outb(PIT_CHANNEL_0_DATA, frequency_lower);
	outb(PIT_CHANNEL_0_DATA, frequency_higher);
}

int PITHandlerIRQ(registers_t* registers) {
	tick++;

    /* Send EOI */
    PICSendEOI(IRQ_TIMER);

    return 1;
}

void SetupPIT() {
	PITSetupTimer(50); // 50 Hz
    PICInstallIRQHandler(IRQ_TIMER, PITHandlerIRQ);
}

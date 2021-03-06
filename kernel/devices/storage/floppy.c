/**
 * floppy.c - Floppy drive routines.
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

#include <arch/io.h>
#include <arch/interrupts.h>
#include <arch/registers.h>

#include <devices/storage/floppy.h>

#include <common.h>

void FloppySetMotor() {

}

void FloppyDetectDrives() {
    outb(0x70, 0x10);

    uint8_t num_drives = inb(0x71);

    printf("[Floppy] Detected Floppy Drive 0: %i\n", (num_drives >> 4));
    printf("[Floppy] Detected Floppy Drive 1: %i\n", (num_drives & 0xF));
}

void SetupFloppy() {

    FloppyDetectDrives();

    outb(FLOPPY_DIGITAL_OUTPUT_REGISTER, FLOPPY_DOR_BIT_DSEL0);



}

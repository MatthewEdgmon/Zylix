/**
 * floppy.h - Floppy disk drives.
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

#ifndef __FLOPPY_H__
#define __FLOPPY_H__

#include <stdint.h>

#define FLOPPY_STATUS_REGISTER_A              0x3F0 /* A.k.a. SRA, read-only */
#define FLOPPY_STATUS_REGISTER_B              0x3F1 /* A.k.a. SRB, read-only */
#define FLOPPY_DIGITAL_OUTPUT_REGISTER        0x3F2 /* A.k.a. DOR */
#define FLOPPY_TAPE_DRIVE_REGISTER            0x3F3
#define FLOPPY_MAIN_STATUS_REGISTER           0x3F4 /* A.k.a. MSR, read-only */
#define FLOPPY_DATARATE_SELECT_REGISTER       0x3F4 /* A.k.a. DSR, write-only */
#define FLOPPY_DATA_FIFO                      0x3F5
#define FLOPPY_DIGITAL_INPUT_REGISTER         0x3F7 /* A.k.a. DIR, read-only */
#define FLOPPY_CONFIGURATION_CONTROL_REGISTER 0x3F7 /* A.k.a. CCR, write-only */

#define FLOPPY_DOR_BIT_DSEL0 0
#define FLOPPY_DOR_BIT_DSEL1 1
#define FLOPPY_DOR_BIT_RESET 2
#define FLOPPY_DOR_BIT_IRQ   3
#define FLOPPY_DOR_BIT_MOTA  4
#define FLOPPY_DOR_BIT_MOTB  5
#define FLOPPY_DOR_BIT_MOTC  6
#define FLOPPY_DOR_BIT_MOTD  7

#define FLOPPY_MSR_BIT_ACTA  0 /* Is drive 0 seeking? */
#define FLOPPY_MSR_BIT_ACTB  1 /* Is drive 1 seeking? */
#define FLOPPY_MSR_BIT_ACTC  2 /* Is drive 2 seeking? */
#define FLOPPY_MSR_BIT_ACTD  3 /* Is drive 3 seeking? */
#define FLOPPY_MSR_BIT_CB    4 /* Command busy. */
#define FLOPPY_MSR_BIT_NDMA  5
#define FLOPPY_MSR_BIT_DIO   6 /* If set, FIFO IO expects IN opcode */
#define FLOPPY_MSR_BIT_RQM   7 /* If set, ok to FIFO */

#define FLOPPY_FIFO_COMMAND_READ_TRACK 2
#define FLOPPY_FIFO_SPECIFY

void SetupFloppy();

#endif /* __FLOPPY_H__ */

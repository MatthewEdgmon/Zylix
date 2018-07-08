/**
 * ata.h - Support code for ATA drives used for all modes.
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

#ifndef __ATA_H__
#define __ATA_H__

#include <stdint.h>

#include <arch/interrupts.h>
#include <arch/registers.h>

#define ATA_SECTOR_SIZE 512

#define ATA_PRIMARY    1
#define ATA_SECONDARY  2
#define ATA_TERTIARY   3
#define ATA_QUATERNARY 4

#define ATA_MASTER     1
#define ATA_SLAVE      2

#define ATA_CONTROL_BIT_NIEN 1
#define ATA_CONTROL_BIT_SRST 2
#define ATA_CONTROL_BIT_HOB  7

#define ATA_STATUS_BIT_ERR 0
#define ATA_STATUS_BIT_DRQ 3
#define ATA_STATUS_BIT_SRV 4
#define ATA_STATUS_BIT_DF  5
#define ATA_STATUS_BIT_RDY 6
#define ATA_STATUS_BIT_BSY 7

#define ATA_DEVICE_UNKNOWN 0
#define ATA_DEVICE_PATAPI  1
#define ATA_DEVICE_SATAPI  2
#define ATA_DEVICE_PATA    3
#define ATA_DEVICE_SATA    4

#define ATA_SELECT_MASTER 0xA0
#define ATA_SELECT_SLAVE  0xB0

#define ATA_COMMAND_READ_SECTORS_EXT  0x24
#define ATA_COMMAND_WRITE_SECTORS_EXT 0x34
#define ATA_COMMAND_IDENTIFY          0xEC

#define ATA_PRIMARY_PORT_DATA               0x1F0
#define ATA_PRIMARY_PORT_FEATURES_ERRORS    0x1F1
#define ATA_PRIMARY_PORT_SECTOR_COUNT       0x1F2
#define ATA_PRIMARY_PORT_LBA_LOW            0x1F3
#define ATA_PRIMARY_PORT_LBA_MID            0x1F4
#define ATA_PRIMARY_PORT_LBA_HIGH           0x1F5
#define ATA_PRIMARY_PORT_DRIVE_HEAD         0x1F6
#define ATA_PRIMARY_PORT_COMMAND            0x1F7
#define ATA_PRIMARY_PORT_STATUS             0x1F7
#define ATA_PRIMARY_CONTROL_REGISTER        0x3F6
#define ATA_PRIMARY_ALTERNATE_STATUS        0x3F6

#define ATA_SECONDARY_PORT_DATA             0x170
#define ATA_SECONDARY_PORT_FEATURES_ERRORS  0x171
#define ATA_SECONDARY_PORT_SECTOR_COUNT     0x172
#define ATA_SECONDARY_PORT_LBA_LOW          0x173
#define ATA_SECONDARY_PORT_LBA_MID          0x174
#define ATA_SECONDARY_PORT_LBA_HIGH         0x175
#define ATA_SECONDARY_PORT_DRIVE_HEAD       0x176
#define ATA_SECONDARY_PORT_COMMAND          0x177
#define ATA_SECONDARY_PORT_STATUS           0x177
#define ATA_SECONDARY_CONTROL_REGISTER      0x376
#define ATA_SECONDARY_ALTERNATE_STATUS      0x376

#define ATA_TERTIARY_PORT_DATA              0x1E8
#define ATA_TERTIARY_PORT_FEATURES_ERRORS   0x1E9
#define ATA_TERTIARY_PORT_SECTOR_COUNT      0x1EA
#define ATA_TERTIARY_PORT_LBA_LOW           0x1EB
#define ATA_TERTIARY_PORT_LBA_MID           0x1EC
#define ATA_TERTIARY_PORT_LBA_HIGH          0x1ED
#define ATA_TERTIARY_PORT_DRIVE_HEAD        0x1EE
#define ATA_TERTIARY_PORT_COMMAND           0x1EF
#define ATA_TERTIARY_PORT_STATUS            0x1EF
#define ATA_TERTIARY_ALTERNATE_STATUS       0x3E6
#define ATA_TERTIARY_CONTROL_REGISTER       0x3E6

#define ATA_QUATERNARY_PORT_DATA            0x168
#define ATA_QUATERNARY_PORT_FEATURES_ERRORS 0x169
#define ATA_QUATERNARY_PORT_SECTOR_COUNT    0x16A
#define ATA_QUATERNARY_PORT_LBA_LOW         0x16B
#define ATA_QUATERNARY_PORT_LBA_MID         0x16C
#define ATA_QUATERNARY_PORT_LBA_HIGH        0x16D
#define ATA_QUATERNARY_PORT_DRIVE_HEAD      0x16E
#define ATA_QUATERNARY_PORT_COMMAND         0x16F
#define ATA_QUATERNARY_PORT_STATUS          0x16F
#define ATA_QUATERNARY_CONTROL_REGISTER     0x366
#define ATA_QUATERNARY_ALTERNATE_STATUS     0x366

#endif /* __ATA_H__ */

/**
 * ata_pio.h - Generic ATA PIO mode driver.
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

#ifndef __ATA_PIO_H__
#define __ATA_PIO_H__

uint8_t ATA_PIO_SoftwareReset(uint8_t bus);
uint8_t ATA_PIO_DetectDevice(uint8_t bus_number, uint8_t device_number);

uint8_t ATA_PIO_PrimaryInterruptHandler(registers_t* regs);
uint8_t ATA_PIO_SecondaryInterruptHandler(registers_t* regs);

void ATA_PIO_TestRead();

void SetupATA_PIO();

#endif /* __ATA_PIO_H__ */

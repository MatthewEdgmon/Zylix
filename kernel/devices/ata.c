/**
 * ata.c - ATA routines and interrupt handler.
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

#include <devices/ata.h>

#include <common.h>

/**
 * Generic ATA PIO mode driver.
 */

uint8_t ata_selected_drive = 0;
uint8_t ata_selected_bus = 0;

uint8_t ata_primary_num_drives = 0;
uint8_t ata_secondary_num_drives = 0;
uint8_t ata_tertiary_num_drives = 0;
uint8_t ata_quaternary_num_drives = 0;

uint8_t ATASoftwareReset(uint8_t bus_number) {

	uint8_t temp = 0;
	uint8_t timeout_counter = 0;
	uint16_t control_register = 0;

	switch(bus_number) {
		case ATA_PRIMARY:
			control_register = ATA_PRIMARY_CONTROL_REGISTER;
			break;
		case ATA_SECONDARY:
			control_register = ATA_SECONDARY_CONTROL_REGISTER;
			break;
		case ATA_TERTIARY:
			control_register = ATA_TERTIARY_CONTROL_REGISTER;
			break;
		case ATA_QUATERNARY:
			control_register = ATA_QUATERNARY_CONTROL_REGISTER;
			break;
		default:
			printf("ATA: Tried to reset a non-existant ATA bus.\n");
			return 1;
			break;
	}

reset_wait:

	/* Set bit 2 of the control register for the specific bus. */
	BIT_SET(temp, ATA_CONTROL_BIT_SRST);
	outb(control_register, temp);

	/* Clear the bit to resume normal operation. */
	BIT_CLEAR(temp, ATA_CONTROL_BIT_SRST);
	outb(control_register, temp);

	/* Give up after 5 tries. */
	if(timeout_counter == 5) {
		printf("ATA: Giving up on reseting ATA bus #%d.\n", bus_number);
		return 1;
	}

	/* Check that BSY is clear. */
	if(BIT_CHECK(control_register, ATA_STATUS_BIT_BSY)) {
		printf("ATA: Waiting some more. Busy bit set.\n");
		timeout_counter++;
		goto reset_wait;
	}

	/* Check that DRQ is set. */
	if(!BIT_CHECK(control_register, ATA_STATUS_BIT_DRQ)) {
		printf("ATA: Waiting some more. DRQ bit not set.\n");
		timeout_counter++;
		goto reset_wait;
	}

	/* After a reset, ATA selects Master. */
	ata_selected_bus = bus_number;
	ata_selected_drive = ATA_MASTER;

	return 0;
}

uint8_t ATADetectDevice(uint8_t bus_number, uint8_t device_number) {

	uint16_t temp = 0;

	/* Ports used to send the identify. */
	uint16_t port_data = 0;
	uint16_t port_sect_num = 0;
	uint16_t port_lba_low = 0;
	uint16_t port_lba_mid = 0;
	uint16_t port_lba_high = 0;
	uint16_t port_drive_head = 0;
	uint16_t port_command = 0;
	uint16_t port_status = 0;

	/* Data read from identify. */

	//uint16_t lba_48_supported;

	//uint16_t udma_modes_supported;

	//uint16_t 48bit_addressable_sectors_1, 48bit_addressable_sectors_2,
	//		 48bit_addressable_sectors_3, 48bit_addressable_sectors_4;

	//uint64_t 48bit_addressable_sectors;

	switch(bus_number) {
		case ATA_PRIMARY:
			port_data = ATA_PRIMARY_PORT_DATA;
		 	port_sect_num = ATA_PRIMARY_PORT_SECTOR_COUNT;
			port_lba_low = ATA_PRIMARY_PORT_LBA_LOW;
		 	port_lba_mid = ATA_PRIMARY_PORT_LBA_MID;
		 	port_lba_high = ATA_PRIMARY_PORT_LBA_HIGH;
		 	port_drive_head = ATA_PRIMARY_PORT_DRIVE_HEAD;
		 	port_command = ATA_PRIMARY_PORT_COMMAND;
		 	port_status = ATA_PRIMARY_PORT_STATUS;
			break;
		case ATA_SECONDARY:
			port_data = ATA_SECONDARY_PORT_DATA;
			port_sect_num = ATA_SECONDARY_PORT_SECTOR_COUNT;
			port_lba_low = ATA_SECONDARY_PORT_LBA_LOW;
			port_lba_mid = ATA_SECONDARY_PORT_LBA_MID;
			port_lba_high = ATA_SECONDARY_PORT_LBA_HIGH;
			port_drive_head = ATA_SECONDARY_PORT_DRIVE_HEAD;
			port_command = ATA_SECONDARY_PORT_COMMAND;
			port_status = ATA_SECONDARY_PORT_STATUS;
			break;
		case ATA_TERTIARY:
			port_data = ATA_TERTIARY_PORT_DATA;
			port_sect_num = ATA_TERTIARY_PORT_SECTOR_COUNT;
			port_lba_low = ATA_TERTIARY_PORT_LBA_LOW;
			port_lba_mid = ATA_TERTIARY_PORT_LBA_MID;
			port_lba_high = ATA_TERTIARY_PORT_LBA_HIGH;
			port_drive_head = ATA_TERTIARY_PORT_DRIVE_HEAD;
			port_command = ATA_TERTIARY_PORT_COMMAND;
			port_status = ATA_TERTIARY_PORT_STATUS;
			break;
		case ATA_QUATERNARY:
			port_data = ATA_QUATERNARY_PORT_DATA;
			port_sect_num = ATA_QUATERNARY_PORT_SECTOR_COUNT;
			port_lba_low = ATA_QUATERNARY_PORT_LBA_LOW;
			port_lba_mid = ATA_QUATERNARY_PORT_LBA_MID;
			port_lba_high = ATA_QUATERNARY_PORT_LBA_HIGH;
			port_drive_head = ATA_QUATERNARY_PORT_DRIVE_HEAD;
			port_command = ATA_QUATERNARY_PORT_COMMAND;
			port_status = ATA_QUATERNARY_PORT_STATUS;
			break;
		default:
			printf("Tried to detect an ATA device on an invalid bus number!\n");
			break;
	}

	/* Select the requested device. */
	outb(port_drive_head, device_number);

	/* Last selected bus/drive is set. */
	ata_selected_bus = bus_number;
	ata_selected_drive = device_number;

	/* Read the status register. */
	temp = inb(port_status);
	temp = inb(port_status);
	temp = inb(port_status);
	temp = inb(port_status);
	temp = inb(port_status);

	/* Check RDY and BSY before setting parameters. */

	outb(port_sect_num, 0x0);
	outb(port_lba_low, 0x0);
	outb(port_lba_mid, 0x0);
	outb(port_lba_high, 0x0);

	/* Send the identify command. */
	outb(port_command, ATA_COMMAND_IDENTIFY);

	temp = inb(port_status);

	if(temp == 0) {
		/* Zero means drive doesn't exist. Done. */
		if(device_number == ATA_MASTER) {
			printf("ATA BUS%d/MASTER does not exist.\n", bus_number);
			return 0;
		} else {
			printf("ATA BUS%d/SLAVE does not exist.\n", bus_number);
			return 0;
		}
	}

	/* Non-zero on the status port, wait until BSY clears. */
	while(BIT_CHECK(temp, ATA_STATUS_BIT_BSY)) {
		temp = inb(port_status);
	}

	/* Poll LBA Mid and LBa High ports to check for ATA. */
	if(inb(port_lba_mid != 0) || inb(port_lba_high != 0)) {
		printf("ATA BUS%d/SLAVE is not an ATA device.\n", bus_number);
		return 1;
	}

	/* Poll the status register until DRQ is clear. */
	while(!BIT_CHECK(temp, ATA_STATUS_BIT_DRQ)) {
		temp = inb(port_status);

		/* Check for errors while waiting for DRQ to set. */
		if(BIT_CHECK(temp, ATA_STATUS_BIT_ERR)) {
			if(device_number == ATA_MASTER) {
				printf("ATA BUS%d/MASTER made an error.\n", bus_number);
				return 1;
			} else {
				printf("ATA BUS%d/SLAVE made an error.\n", bus_number);
				return 1;
			}
		}
	}

	/* Output all 256 16 bit values of the device. */
	for(size_t i = 0; i < 256; i++) {
		printf("%X", inb(port_data));
	}

	/* And say this device exists. */
	return 1;
}

uint8_t ATAPrimaryInterruptHandler(registers_t* regs) {
	uint8_t status = inb(ATA_PRIMARY_PORT_STATUS);

	while(BIT_CHECK(status, ATA_STATUS_BIT_BSY)) {
		status = inb(ATA_PRIMARY_PORT_STATUS);
	}

	uint16_t buffer[256];

	printf("\nATA: Got a Primary ATA interrupt. Status: 0x%X ", status);

	if(BIT_CHECK(status, ATA_STATUS_BIT_ERR)) { printf("ERR "); }
	if(BIT_CHECK(status, ATA_STATUS_BIT_DRQ)) { printf("DRQ "); }
	if(BIT_CHECK(status, ATA_STATUS_BIT_SRV)) { printf("SRV "); }
	if(BIT_CHECK(status, ATA_STATUS_BIT_DF )) { printf("DF "); }
	if(BIT_CHECK(status, ATA_STATUS_BIT_RDY)) { printf("RDY "); }
	if(BIT_CHECK(status, ATA_STATUS_BIT_BSY)) { printf("BSY "); }
	printf("\n");

	for(size_t i = 0; i < 255; i++) {
		buffer[i] = inw(ATA_PRIMARY_PORT_DATA);
	}

	//for(size_t i = 0; i < 255; i++) {
	//	printf("%5X\n", buffer[i]);
	//}

	printf("\n");

	PICSendEOI(IRQ_PRIMARY_IDE);

	return 1;
}

uint8_t ATASecondaryInterruptHandler(registers_t* regs) {
	uint8_t status = inb(ATA_SECONDARY_PORT_STATUS);

	while(BIT_CHECK(status, ATA_STATUS_BIT_BSY)) {
		status = inb(ATA_PRIMARY_PORT_STATUS);
	}

	uint16_t buffer[256];

	printf("\nATA: Got a Secondary ATA interrupt. Status: 0x%X ", status);

	if(BIT_CHECK(status, ATA_STATUS_BIT_ERR)) { printf("ERR "); }
	if(BIT_CHECK(status, ATA_STATUS_BIT_DRQ)) { printf("DRQ "); }
	if(BIT_CHECK(status, ATA_STATUS_BIT_SRV)) { printf("SRV "); }
	if(BIT_CHECK(status, ATA_STATUS_BIT_DF )) { printf("DF "); }
	if(BIT_CHECK(status, ATA_STATUS_BIT_RDY)) { printf("RDY "); }
	if(BIT_CHECK(status, ATA_STATUS_BIT_BSY)) { printf("BSY "); }
	printf("\n");

	for(size_t i = 0; i < 255; i++) {
		buffer[i] = inw(ATA_PRIMARY_PORT_DATA);
	}

	//for(size_t i = 0; i < 255; i++) {
	//	printf("%5X\n", buffer[i]);
	//}

	printf("\n");

	PICSendEOI(IRQ_SECONDARY_IDE);

	return 1;
}

void ATAReadTest() {

	/* Test Read. */
	uint8_t sector_count_high = 0x0;
	uint8_t sector_count_low = 0x0; // Sector count of 0 means 256
	uint8_t lba_test_byte_1 = 0x1;
	uint8_t lba_test_byte_2 = 0x0;
	uint8_t lba_test_byte_3 = 0x0;
	uint8_t lba_test_byte_4 = 0x0;
	uint8_t lba_test_byte_5 = 0x0;
	uint8_t lba_test_byte_6 = 0x0;

	/* Select slave drive. */
	outb(ATA_PRIMARY_PORT_DRIVE_HEAD, 0x50);
	/* Send sector_count high byte. */
	outb(ATA_PRIMARY_PORT_SECTOR_COUNT, sector_count_high);
	/* Send LBA bytes 4 to 6 */
	outb(ATA_PRIMARY_PORT_LBA_LOW, lba_test_byte_4);
	outb(ATA_PRIMARY_PORT_LBA_MID, lba_test_byte_5);
	outb(ATA_PRIMARY_PORT_LBA_HIGH, lba_test_byte_6);
	/* Send sector_count low byte. */
	outb(ATA_PRIMARY_PORT_SECTOR_COUNT, sector_count_low);
	/* Send LBA bytes 1 to 3 */
	outb(ATA_PRIMARY_PORT_LBA_LOW, lba_test_byte_1);
	outb(ATA_PRIMARY_PORT_LBA_MID, lba_test_byte_2);
	outb(ATA_PRIMARY_PORT_LBA_HIGH, lba_test_byte_3);
	/* Send the read command. */
	outb(ATA_PRIMARY_PORT_COMMAND, ATA_COMMAND_READ_SECTORS_EXT);

	/* Should get an IRQ at this point. */
}

/**
 * NOTICE: In most cases, if it exists, PCI Configuration Space should be polled
 * first to find the actual control registers and IRQs for each ATA bus. The PCI
 * specs state that all disk controllers ports should be set to standard.
 */
void SetupATA() {

    /* Disable interrupts. */
    PICSetMask(IRQ_PRIMARY_IDE);
    PICSetMask(IRQ_SECONDARY_IDE);
    PICDisableInterrupts();

    /* Install handlers. */
    PICInstallIRQHandler(IRQ_PRIMARY_IDE, ATAPrimaryInterruptHandler);
    PICInstallIRQHandler(IRQ_SECONDARY_IDE, ATASecondaryInterruptHandler);

	/* Detect number of drives for each bus. */

	if(inb(ATA_PRIMARY_PORT_STATUS) == 0xFF) {
		ata_primary_num_drives = 0;
	} else {
		if(ATADetectDevice(ATA_PRIMARY, ATA_MASTER)) {
			ata_primary_num_drives += 1;
		}
		if(ATADetectDevice(ATA_PRIMARY, ATA_SLAVE)) {
			ata_primary_num_drives += 1;
		}
	}

	if(inb(ATA_SECONDARY_PORT_STATUS) == 0xFF) {
		ata_secondary_num_drives = 0;
	} else {
		if(ATADetectDevice(ATA_SECONDARY, ATA_MASTER)) {
			ata_secondary_num_drives += 1;
		}
		if(ATADetectDevice(ATA_SECONDARY, ATA_SLAVE)) {
			ata_secondary_num_drives += 1;
		}
	}

	if(inb(ATA_TERTIARY_PORT_STATUS) == 0xFF) {
		ata_tertiary_num_drives = 0;
	} else {
		if(ATADetectDevice(ATA_TERTIARY, ATA_MASTER)) {
			ata_tertiary_num_drives += 1;
		}
		if(ATADetectDevice(ATA_TERTIARY, ATA_SLAVE)) {
			ata_tertiary_num_drives += 1;
		}
	}

	if(inb(ATA_QUATERNARY_PORT_STATUS) == 0xFF) {
		ata_quaternary_num_drives = 0;
	} else {
		if(ATADetectDevice(ATA_QUATERNARY, ATA_MASTER)) {
			ata_quaternary_num_drives += 1;
		}
		if(ATADetectDevice(ATA_QUATERNARY, ATA_SLAVE)) {
			ata_quaternary_num_drives += 1;
		}
	}

	uint16_t num_total_drives = ata_primary_num_drives + ata_secondary_num_drives +
								ata_tertiary_num_drives + ata_quaternary_num_drives;

	printf("ATA Total Drives = %d\n", num_total_drives);

    /* Renable interrupts. */
    PICEnableInterrupts();
    PICClearMask(IRQ_PRIMARY_IDE);
    PICClearMask(IRQ_SECONDARY_IDE);

	/* Software reset test. */
	//ATASoftwareReset(ATA_PRIMARY);
}

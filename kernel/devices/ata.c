#include <stdint.h>

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

uint8_t ATASoftwareReset(uint8_t bus) {

	uint8_t temp = 0;
	uint8_t timeout_counter = 0;
	uint16_t control_register = 0;

	switch(bus) {
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

	/* Set bit 2 of the control register for the specific bus. */
	BIT_SET(temp, ATA_CONTROL_BIT_SRST);
	outb(control_register, temp);

	/* Clear the bit to resume normal operation. */
	BIT_CLEAR(temp, ATA_CONTROL_BIT_SRST);
	outb(control_register, temp);

	/* Wait 400ns */
	temp = inb(control_register);
	temp = inb(control_register);
	temp = inb(control_register);
	temp = inb(control_register);

reset_wait:
	temp = inb(control_register);

	/* Give up after 5 tries. */
	if(timeout_counter == 5) {
		printf("ATA: Giving up on reseting ATA bus #%d.\n", bus);
		return 1;
	}

	/* Check that RDY is set. */
	if(!BIT_CHECK(control_register, ATA_STATUS_BIT_RDY)) {
		printf("ATA: Waiting some more. Ready bit not set.\n");
		timeout_counter++;
		goto reset_wait;
	}

	/* Check that BSY is clear. */
	if(BIT_CHECK(control_register, ATA_STATUS_BIT_BSY)) {
		printf("ATA: Waiting some more. Busy bit set.\n");
		timeout_counter++;
		goto reset_wait;
	}

	/* Set all the control register bits to 0, just in case. */
	temp = 0;
	outb(control_register, temp);

	/* After a reset, ATA selects Master. */
	ata_selected_drive = ATA_MASTER;

	return 0;
}

uint8_t ATAPrimaryInterruptHandler(registers_t* regs) {
	uint8_t temp = inb(ATA_PRIMARY_PORT_STATUS);

	printf("ATA: Got a Primary ATA interrupt.\n");

	PICSendEOI(IRQ_PRIMARY_IDE);

	return 1;
}

uint8_t ATASecondaryInterruptHandler(registers_t* regs) {
	uint8_t temp = inb(ATA_SECONDARY_PORT_STATUS);

	printf("ATA: Got a Secondary ATA interrupt.\n");

	PICSendEOI(IRQ_SECONDARY_IDE);

	return 1;
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

    /* Renable interrupts. */
    PICEnableInterrupts();
    PICClearMask(IRQ_PRIMARY_IDE);
    PICClearMask(IRQ_SECONDARY_IDE);

	/* Software reset test. */
	//ATASoftwareReset(ATA_PRIMARY);
}

/**
 * PIC.c
 *
 * Sets up the Programmable Interrupt Controller, including interrupts, and handlers.
 *
 */

#include <arch/IO.h>

#include <types.h>

#define PIC1                0x20 /* IO base address for master PIC */
#define PIC2                0xA0 /* IO base address for slave PIC */
#define PIC1_COMMAND        PIC1
#define PIC1_DATA           (PIC1+1)
#define PIC2_COMMAND        PIC2
#define PIC2_DATA           (PIC2+1)
#define PIC_EOI             0x20 /* End-of-interrupt command code */

#define ICW1_ICW4           0x01 /* ICW4 (not) needed */
#define ICW1_SINGLE         0x02 /* Single (cascade) mode */
#define ICW1_INTERVAL4      0x04 /* Call address interval 4 (8) */
#define ICW1_LEVEL          0x08 /* Level triggered (edge) mode */
#define ICW1_INIT           0x10 /* Initialization - required! */
 
#define ICW4_8086           0x01 /* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO           0x02 /* Auto (normal) EOI */
#define ICW4_BUF_SLAVE      0x08 /* Buffered mode/slave */
#define ICW4_BUF_MASTER     0x0C /* Buffered mode/master */
#define ICW4_SFNM           0x10 /* Special fully nested (not) */

#define SYNC_CLI()          __asm__ __volatile__("cli")
#define SYNC_STI()          __asm__ __volatile__("sti")

uint32_t timer_tick = 0;

/* reinitialize the PIC controllers, giving them specified vector offsets
   rather than 8h and 70h, as configured by default */

void DisableInterrupts() {
	SYNC_CLI();
}

void EnableInterrupts() {
	SYNC_STI();
}

void ResumeInterrupts() {

}

void InstallIRQHandler() {

}

void UninstallIRQHandler() {

}

void IRQHandler(struct registers *regs) {
	/* Getting an interrupt during an interrupt is a no-no. */
	DisableInterrupts();
}

/**
 * arguments:
 *	offset1 - vector offset for master PIC vectors on the master become offset1..offset1+7
 *	offset2 - same for slave PIC: offset2..offset2+7
 */
void RemapPIC(int offset1, int offset2) {

	/* Save PIC masks. */
	unsigned char mask1, mask2;

	mask1 = inb(PIC1_DATA);
	mask2 = inb(PIC2_DATA);

	/* Initialize both PICs in cascade mode. */
	outb(PIC1_COMMAND, ICW1_INIT+ICW1_ICW4);
	io_wait();
	outb(PIC2_COMMAND, ICW1_INIT+ICW1_ICW4);
	io_wait();

	/* Set vector offsets for master and slave. */
	outb(PIC1_DATA, offset1);
	io_wait();
	outb(PIC2_DATA, offset2);
	io_wait();

	/* Tell the master it has a slave, and tell the slave it has a master at IRQ2 (0000 0100) */
	outb(PIC1_DATA, 4);
	io_wait();
	outb(PIC2_DATA, 2);
	io_wait();

	/* Tell the PIC it's in 8086 mode. */
	outb(PIC1_DATA, ICW4_8086);
	io_wait();
	outb(PIC2_DATA, ICW4_8086);
	io_wait();

	/* Restore saved PIC masks. */
	outb(PIC1_DATA, mask1);
	outb(PIC2_DATA, mask2);

}

/*
void SetIRQMask(unsigned char request_line) {
	uint16_t port;
	uint8_t value;

	if(request_line < 8) {
		port = PIC1_DATA;
	} else
		port = PIC2_DATA;
		request_line -= 8;
	}

	value = inb(port) | (1 << request_line);
	outb(port, value);
}

void ClearIRQMask(unsigned char request_line) {
	uint16_t port;
	uint8_t value;

	if(request_line < 8) {
		port = PIC1_DATA;
	} else
		port = PIC2_DATA;
		request_line -= 8;
	}

	value = inb(port) & ~(1 << request_line);
	outb(port, value);
}*/

/**
 * Tell the PIC we are done handling an IRQ, and optionally tell the slave.
 */
void SendEOI(uint8_t IRQ) {

	/* If the interrupt came from the slave PIC, pass the EOI to it too. */
	if(IRQ >= 8) {
		outb(PIC2_COMMAND, PIC_EOI);
 	}

	outb(PIC1_COMMAND, PIC_EOI);
}

/* Useful in circumstances like using the APIC and IOAPIC */
void DisablePIC() {
	outb(PIC2_DATA, 0xFF);
	io_wait();
	outb(PIC1_DATA, 0xFF);
	io_wait();
}

/* Is run everytime the PIT fires. */
static void TimerCallback() {
	timer_tick++;
}

/* Setup the PIT with a specific frequency. */
void SetupTimer(uint32_t frequency) {

	/* TODO: Register timer callback handler. */
	//RegisterInterruptHandler(IRQ0, &TimerCallback);

	uint32_t divisor = 1193180 / frequency;

	/* Send the command byte. */
	outb(0x43, 0x36);

	uint8_t frequency_lower = (uint8_t)(divisor & 0xFF);
	uint8_t frequency_higher = (uint8_t)( (divisor>>8) & 0xFF);

	/* Send the frequency divisor. */
	outb(0x40, frequency_lower);
	outb(0x40, frequency_higher);

}

void SetupIRQ() {
	
}

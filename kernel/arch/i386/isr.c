#include "i386.h"

#include <terminal.h>

/* The count is treated as is when setting up IDT gates. However there is an
 * additional ISR for the system call vector which is handled explicitly since
 * it's mapped at a different address.
 */
#define ISR_COUNT 32

static struct {
	size_t index;
	void (*stub)(void);
} isrs[32 + 1] __attribute__((used));

static irq_handler_t isr_routines[256] = { 0 };

void InstallISRHandler(size_t isrs, irq_handler_t handler) {
	isr_routines[isrs] = handler;
}

void UninstallISRHandler(size_t isrs) {
	isr_routines[isrs] = 0;
}

void SetupISR(void) {
	char buffer[16];
	for (int i = 0; i < ISR_COUNT; i++) {
		//sprintf(buffer, "_isr%d", i);
		isrs[i].index = i;
		//isrs[i].stub = symbol_find(buffer);
	}
	//isrs[ISR_COUNT].index = SYSCALL_VECTOR;
	//isrs[ISR_COUNT].stub = symbol_find("_isr127");

	for (int i = 0; i < ISR_COUNT + 1; i++) {
		CreateIDTEntry(isrs[i].index, isrs[i].stub, 0x08, 0x8E);
	}
}

void ISRFaultHandler(struct registers *regs) {
	irq_handler_t handler = isr_routines[regs->interrupt_number];
	if(handler) {
		handler(regs);
	} else {
		TerminalPrintString("Caught an unhandled exception, you should probably fix that.");
	}
}
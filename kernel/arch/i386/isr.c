#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include <arch/interrupts.h>

#include "i386.h"
#include "isr.h"
#include "idt.h"

/* The count is treated as is when setting up IDT gates. However there is an
 * additional ISR for the system call vector which is handled explicitly since
 * it's mapped at a different address.
 */
#define ISR_COUNT 32

/* Our ISRs */
extern void  isr0();
extern void  isr1();
extern void  isr2();
extern void  isr3();
extern void  isr4();
extern void  isr5();
extern void  isr6();
extern void  isr7();
extern void  isr8();
extern void  isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();
//extern void isr32();
//extern void isr33();
//extern void isr_syscall();
extern void isr99();

static const char *exception_messages[32] = {
    "Division by zero",
    "Debug",
    "Non-Maskable Interrupt",
    "Breakpoint",
    "Detected Overflow",
    "Out-of-bounds",
    "Invalid Opcode",
    "No Coprocessor",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",
    "Coprocessor fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

static struct {
	size_t index;
	void (*stub)(void);
} isrs[32 + 1] __attribute__((used));

static irq_handler_t isr_routines[256] = { 0 };

void ISRInstallHandler(size_t isrs, irq_handler_t handler) {
	isr_routines[isrs] = handler;
}

void ISRUninstallHandler(size_t isrs) {
	isr_routines[isrs] = 0;
}

void ISRFaultHandler(struct registers *regs) {
	irq_handler_t handler = isr_routines[regs->interrupt_number];
	if(handler) {
        printf("Handling ISR #%d\n", regs->interrupt_number);
		handler(regs);
	} else {
		printf("Unhandled exception: [%d] %s \n", regs->interrupt_number, exception_messages[regs->interrupt_number]);
	}
}

typedef void (*func_pointer_t)();

func_pointer_t isr_functions[] = {
    isr0,   isr1,  isr2,  isr3,  isr4,
    isr5,   isr6,  isr7,  isr8,  isr9,
    isr10, isr11, isr12, isr13, isr14,
    isr15, isr16, isr17, isr18, isr19,
    isr20, isr21, isr22, isr23, isr24,
    isr25, isr26, isr27, isr28, isr29,
    isr30, isr31,

    /* Last one is always syscall. */
    isr99
};

void SetupISR(void) {
    for(int i = 0; i < ISR_COUNT; i++) {
        isrs[i].index = i;
        isrs[i].stub = isr_functions[i];
    }

	isrs[ISR_COUNT].index = SYSCALL_VECTOR;
	isrs[ISR_COUNT].stub = isr_functions[ISR_COUNT];

	for(int i = 0; i < ISR_COUNT + 1; i++) {
		IDTCreateEntry(isrs[i].index, isrs[i].stub, 0x08, 0x8E);
	}

    return;
}

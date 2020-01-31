/**
 * isr.c - x86_64 Interrupt Service Routines
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

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include <arch/interrupts.h>
#include <arch/registers.h>

#include "x86_64.h"
#include "isr.h"
#include "idt.h"

/* The count is treated as is when setting up IDT gates. However there is an
 * additional ISR for the system call vector which is handled explicitly since
 * it's mapped at a different address.
 */
#define ISR_COUNT 32

/* Our ISRs */
extern void  isr0();    /* Divison by zero. */
extern void  isr1();    /* Debug. */
extern void  isr2();    /* Non-Maskable Interrupt. */
extern void  isr3();    /* Breakpoint. */
extern void  isr4();    /* Detected Overflow. */
extern void  isr5();    /* Out-of-bounds. */
extern void  isr6();    /* Invalid Opcode. */
extern void  isr7();    /* No Coprocessor. */
extern void  isr8();    /* Double fault. */
extern void  isr9();    /* Coprocessor Segment Overrun. */
extern void isr10();    /* Bad TSS. */
extern void isr11();    /* Segment not present. */
extern void isr12();    /* Stack fault. */
extern void isr13();    /* General Protection Fault. */
extern void isr14();    /* Page Fault. */
extern void isr15();    /* Unkown interrupt. */
extern void isr16();    /* Coprocessor fault. */
extern void isr17();    /* Alignment Check. */
extern void isr18();    /* Machine Check. */
extern void isr19();    /* Reserved. */
extern void isr20();    /* Reserved. */
extern void isr21();    /* Reserved. */
extern void isr22();    /* Reserved. */
extern void isr23();    /* Reserved. */
extern void isr24();    /* Reserved. */
extern void isr25();    /* Reserved. */
extern void isr26();    /* Reserved. */
extern void isr27();    /* Reserved. */
extern void isr28();    /* Reserved. */
extern void isr29();    /* Reserved. */
extern void isr30();    /* Reserved. */
extern void isr31();    /* Reserved. */
extern void isr99();    /* System call. */

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

void ISRFaultHandler(cpu_registers_t* regs) {
    irq_handler_t handler = isr_routines[regs->interrupt_number];
    if(handler) {
        printf("Handling ISR [%d] %s \n", regs->interrupt_number, exception_messages[regs->interrupt_number]);
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

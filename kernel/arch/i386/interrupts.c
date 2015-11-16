/**
 * This file handles all of interrupts, including ISR, IDT, etc.
 */
#include "interrupts.h"

#include <libc/stdint.h>
#include <libc/string.h>

#define NUMBER_OF_ISRS 34

extern void LoadIDT();

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
extern void isr32();
extern void isr33();
extern void isr_syscall();

/**
 * An entry in the IDT.
 */
typedef struct {
    uint16_t    base_low;
    uint16_t    selector;
    uint8_t     zero;
    uint8_t     flags;
    uint16_t    base_high;
} __attribute__((packed)) idt_entry_t;

/**
 * Pointer to where the IDT resides.
 */
typedef struct {
    uint16_t        limit;
    uintptr_t       base;
} __attribute__((packed)) idt_pointer_t;

/**
 * The actual IDT.
 */
/* In the future we may need to put a lock on the access of this */
static struct {
    idt_entry_t entries[256];
    idt_pointer_t pointer;
} idt __attribute__((used));

#define IDT_ENTRY(X) (idt.entries[(X)])

static const char *exception_messages[32] = {
    "Division by zero",
    "Debug",
    "Non-maskable interrupt",
    "Breakpoint",
    "Detected overflow",
    "Out-of-bounds",
    "Invalid opcode",
    "No coprocessor",
    "Double fault",
    "Coprocessor segment overrun",
    "Bad TSS",
    "Segment not present",
    "Stack fault",
    "General protection fault",
    "Page fault",
    "Unknown interrupt",
    "Coprocessor fault",
    "Alignment check",
    "Machine check",
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

void IDTCreateEntry(uint32_t base, uint16_t selector, uint8_t flags, uint8_t index) {
    IDT_ENTRY(index).base_low  = ((uintptr_t)base &  0xFFFF);
    IDT_ENTRY(index).base_high = ((uintptr_t)base >> 16) & 0xFFFF;
    IDT_ENTRY(index).selector  = selector;
    IDT_ENTRY(index).zero      = 0;
    IDT_ENTRY(index).flags     = flags | 0x60;
}

void IDTInitialize() {
    /* Exception handling IDTs. */
    /* Normal IRQs. */
    /* Syscall. */
}

void FaultHandler() {

}

void SetupIDT() {
    idt_pointer_t* idt_pointer = &idt.pointer;
    idt_pointer->limit = sizeof idt.entries - 1;
    idt_pointer->base = (uintptr_t)&IDT_ENTRY(0);
    memset(&IDT_ENTRY(0), 0, sizeof idt.entries);
    LoadIDT((uintptr_t) idt_pointer);
}

void SetupInterrupts() {
    SetupIDT();
}
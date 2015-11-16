#ifndef __I386_H__
#define __I386_H__

/**
 * Collection of variables, defines, and functions not visible globally, only for this arch.
 */

#include <libc/stdint.h>

#define SYSCALL_VECTOR 0x90

#define USER_STACK_BOTTOM 0xAFF00000
#define USER_STACK_TOP    0xB0000000

struct registers {
	unsigned int GS, FS, ES, DS;
	unsigned int EDI, ESI, EBP, ESP, EBX, EDX, ECX, EAX;
	unsigned int interrupt_number, error_code;
	unsigned int EIP, CS, eflags, useresp, SS;
};

/* ISR.c */
typedef struct registers registers_t;

typedef void (*irq_handler_t) (struct registers *);
typedef int (*irq_handler_chain_t) (struct registers *);

void SetupISR();

/* CPU.c */
uint64_t rdtsc();

/* CPUInfo.c */
void StoreCPUInformation(void);

/* GDT.c */
void SetupGDT();

/* IDT.c */
typedef void (*idt_gate_t)(void);

void SetupIDT();
void CreateIDTEntry(uint8_t entry_number, idt_gate_t base, uint16_t sel, uint8_t flags);

/* IRQ.c */
void RemapIRQ();
void SetupIRQ();

#endif /* __I386_H__ */
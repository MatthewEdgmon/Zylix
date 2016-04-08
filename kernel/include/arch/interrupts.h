#ifndef __INTERRUPTS_H__
#define __INTERRUPTS_H__

#include <libc/stdint.h>
#include <libc/stddef.h>

/* IRQ numbers. */
#define IRQ_TIMER 0
#define IRQ_KEYBOARD 1
#define IRQ_CASCADE 2
#define IRQ_SERIAL2 3
#define IRQ_SERIAL1 4
#define IRQ_SOUND 5
#define IRQ_FLOPPY 6
#define IRQ_PARALLEL 7
#define IRQ_RTC 8
#define IRQ_MOUSE 12
#define IRQ_FPU 13
#define IRQ_PRIMARY_IDE 14
#define IRQ_SECONDARY_IDE 15

struct registers {
	unsigned int GS, FS, ES, DS;
	unsigned int EDI, ESI, EBP, ESP, EBX, EDX, ECX, EAX;
	unsigned int interrupt_number, error_code;
	unsigned int EIP, CS, eflags, useresp, SS;
};

typedef struct registers registers_t;

typedef void (*irq_handler_t) (struct registers *);
typedef int (*irq_handler_chain_t) (struct registers *);

#include "../../arch/i386/isr.h"
#include "../../arch/i386/pic.h"

#endif /* __INTERRUPTS_H__ */

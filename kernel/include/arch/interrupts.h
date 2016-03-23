#ifndef __INTERRUPTS_H__
#define __INTERRUPTS_H__

#include <libc/stdint.h>
#include <libc/stddef.h>

struct registers {
	unsigned int GS, FS, ES, DS;
	unsigned int EDI, ESI, EBP, ESP, EBX, EDX, ECX, EAX;
	unsigned int interrupt_number, error_code;
	unsigned int EIP, CS, eflags, useresp, SS;
};

typedef struct registers registers_t;

typedef void (*irq_handler_t) (struct registers *);
typedef int (*irq_handler_chain_t) (struct registers *);

void ISRInstallHandler(size_t isrs, irq_handler_t handler);
void ISRUninstallHandler(size_t isrs);
void ISRFaultHandler(struct registers *regs);

#endif /* __INTERRUPTS_H__ */

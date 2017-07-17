#ifndef __INTERRUPTS_H__
#define __INTERRUPTS_H__

#include <stdint.h>
#include <stddef.h>

#include <arch/registers.h>

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

typedef void (*irq_handler_t) (struct registers *);
typedef int (*irq_handler_chain_t) (struct registers *);

/**
 * Using generic names will help cross-platform in the future.
 */
#define InterruptsDisable PICDisableInterrupts
#define InterruptsEnable PICEnableInterrupts
#define InterruptsResume PICResumeInterrupts
#define InterruptsInstallHandler PICInstallIRQHandler

#include "../../arch/i686/gdt.h"
#include "../../arch/i686/isr.h"
#include "../../arch/i686/pic.h"

#endif /* __INTERRUPTS_H__ */

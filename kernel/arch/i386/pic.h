#ifndef __PIC_H__
#define __PIC_H__

#include <libc/stdint.h>

#include <arch/interrupts.h>

void PICDisableInterrupts();
void PICEnableInterrupts();
void PICResumeInterrupts();
void PICInstallIRQHandler(size_t irq, irq_handler_chain_t handler);
void PICUninstallIRQHandler(size_t irq);
void PICHandlerIRQ(registers_t *regs);
void PICSetMask(uint16_t irq);
void PICClearMask(uint16_t irq);
void PICRemap(int first_offset, int second_offset);
void PICSendEOI(unsigned int irq);
void PICDisable();
void PICSetupTimer(uint32_t frequency);
void SetupPIC();

#endif /* __PIC_H__ */

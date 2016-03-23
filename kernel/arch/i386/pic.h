#ifndef __PIC_H__
#define __PIC_H__

#include <libc/stdint.h>

#include <arch/interrupts.h>

void PICDisableInterrupts();
void PICEnableInterrupts();
void PICResumeInterrupts();
void PICInstallIRQHandler();
void PICUninstallIRQHandler();
void PICHandlerIRQ();
void PICRemap(int first_offset, int second_offset);
void PICSendEOI(unsigned char irq);
void PICDisable();
void PICSetupTimer(uint32_t frequency);
void SetupPIC();

#endif /* __PIC_H__ */

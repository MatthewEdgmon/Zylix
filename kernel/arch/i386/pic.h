#ifndef __PIC_H__
#define __PIC_H__

void DisableInterrupts();
void EnableInterrupts();
void ResumeInterrupts();
void InstallIRQHandler();
void UninstallIRQHandler();
void RemapPIC(int firstOffset, int secondOffset);
void SendEOI(uint8_t IRQ);
void DisablePIC();
void SetupTimer(uint32_t frequency);

#endif /* __PIC_H__ */
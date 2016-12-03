#ifndef __ISR_H__
#define __ISR_H__

void ISRInstallHandler(size_t isrs, irq_handler_t handler);
void ISRUninstallHandler(size_t isrs);
void ISRFaultHandler(struct registers *regs);

void SetupISR();

#endif /* __ISR_H__ */

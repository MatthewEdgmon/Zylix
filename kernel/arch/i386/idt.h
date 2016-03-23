#ifndef __IDT_H__
#define __IDT_H__

#include <libc/stdint.h>

typedef void (*idt_gate_t)(void);

void IDTCreateEntry(uint8_t entry_number, idt_gate_t base, uint16_t sel, uint8_t flags);

void SetupIDT();

#endif /* __IDT_H__ */

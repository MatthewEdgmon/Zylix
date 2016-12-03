#ifndef __GDT_H__
#define __GDT_H__

#include <stdint.h>

void GDTSetKernelStack(uintptr_t stack);
void GDTCreateEntry(uint8_t entry_number, uint64_t base, uint64_t limit, uint8_t access, uint8_t gran);
static void TSSCreateEntry(uint8_t entry_number, uint16_t ss0, uint32_t esp0);

void SetupGDT();

#endif /* __GDT_H__ */

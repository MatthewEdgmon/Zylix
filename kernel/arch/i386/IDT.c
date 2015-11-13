#include "i386.h"

#include <types.h>

#include <libc.h>

typedef struct {
	uint16_t	base_low;
	uint16_t	sel;
	uint8_t		zero;
	uint8_t		flags;
	uint16_t 	base_high;
} __attribute__((packed)) idt_entry_t;

typedef struct {
	uint16_t		limit;
	uintptr_t		base;
} __attribute__((packed)) idt_pointer_t;

static struct {
	idt_entry_t 	idt_entries[256];
	idt_pointer_t	idt_pointer;
} idt __attribute__((used));

extern void LoadIDT(uintptr_t);

void CreateIDTEntry(uint8_t entry_number, idt_gate_t base, uint16_t sel, uint8_t flags) {
	idt.idt_entries[entry_number].base_low	= ((uintptr_t)base & 0xFFFF);
	idt.idt_entries[entry_number].base_high = ((uintptr_t)base >> 16) & 0xFFFF;
	idt.idt_entries[entry_number].sel 		= sel;
	idt.idt_entries[entry_number].zero		= 0;
	idt.idt_entries[entry_number].flags		= flags | 0x60;
}

void SetupIDT() {
	
	idt_pointer_t * idt_pointer = &idt.idt_pointer;
	idt_pointer->limit 		 	= sizeof idt.idt_entries - 1;
	idt_pointer->base 			= (uintptr_t)&idt.idt_entries[0];
	
	memset(&idt.idt_entries[0], 0, sizeof idt.idt_entries);

	LoadIDT((uintptr_t) idt_pointer);
}
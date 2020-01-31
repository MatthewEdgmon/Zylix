/**
 * idt.c - x86_64 Interrupt Descriptor Table management.
 *
 * This file is part of Zylix.
 *
 * Zylix is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Zylix is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Zylix.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdint.h>
#include <string.h>

typedef struct {
    uint16_t       limit;   /* Defines the length of the IDT in bytes. */
    uintptr_t      base;    /* Linear address where the IDT starts. */
} __attribute__((packed)) idt_pointer_t;

typedef struct {
    uint16_t       base_low;
    uint16_t       selector;
    uint8_t        zero;
    uint8_t        flags;
    uint16_t       base_high;
} __attribute__((packed)) idt_entry_t;

/**
 * The actual IDT.
 */
/* In the future we may need to put a lock on the access of this */
static struct {
    idt_entry_t entries[256];
    idt_pointer_t pointer;
} idt __attribute__((used));

typedef void (*idt_gate_t)(void);

#define ENTRY(X) (idt.entries[(X)])

extern void LoadIDT(uintptr_t);

void IDTCreateEntry(uint8_t number, idt_gate_t base, uint16_t sel, uint8_t flags) {
	ENTRY(number).base_low	= ((uintptr_t)base & 0xFFFF);
	ENTRY(number).base_high = ((uintptr_t)base >> 16) & 0xFFFF;
	ENTRY(number).selector  = sel;
	ENTRY(number).zero		= 0;
	ENTRY(number).flags		= flags | 0x60;
}

void SetupIDT() {

	idt_pointer_t * idt_pointer = &idt.pointer;
	idt_pointer->limit 		 	= sizeof(idt.entries) - 1;
	idt_pointer->base 			= (uintptr_t)&idt.entries[0];

	memset(&ENTRY(0), 0, sizeof(idt.entries));

	LoadIDT((uintptr_t) idt_pointer);
}

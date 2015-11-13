#include "i386.h"

#include <types.h>

#include <libc.h>

/**
 * Structure of one GDT entry.
 */
typedef struct {
	/* Limits */
	uint16_t limit_low;
	/* Segment address */
	uint16_t base_low;
	uint8_t base_middle;
	/* Access modes */
	uint8_t access;
	uint8_t granularity;
	uint8_t base_high;
} __attribute__((packed)) gdt_entry_t;

/**
 * Structure of the TSS entry.
 */
typedef struct {
	uint32_t prev_tss;
	uint32_t esp0;
	uint32_t ss0;
	uint32_t esp1;
	uint32_t ss1;
	uint32_t esp2;
	uint32_t ss2;
	uint32_t cr3;
	uint32_t eip;
	uint32_t eflags;
	uint32_t eax;
	uint32_t ecx;
	uint32_t edx;
	uint32_t ebx;
	uint32_t esp;
	uint32_t ebp;
	uint32_t esi;
	uint32_t edi;
	uint32_t es;
	uint32_t cs;
	uint32_t ss;
	uint32_t ds;
	uint32_t fs;
	uint32_t gs;
	uint32_t ldt;
	uint16_t trap;
	uint16_t iomap_base;
} __attribute__ ((packed)) tss_entry_t;

/**
 * Structure of the GDT pointer.
 */
typedef struct {
	uint16_t  limit;
	uintptr_t base;
} __attribute__((packed)) gdt_pointer_t;

/**
 * The GDT itself.
 */
static struct {
	gdt_entry_t		gdt_entries[6];
	gdt_pointer_t	gdt_pointer;
	tss_entry_t		tss_entry;
} gdt __attribute__((used));

extern void FlushGDT(uintptr_t);
extern void FlushTSS(void);

void SetKernelStack(uintptr_t stack) {
	gdt.tss_entry.esp0 = stack;
}

void CreateGDTEntry(uint8_t entry_number, uint64_t base, uint64_t limit, uint8_t access, uint8_t gran) {
	/* Base Address */
	gdt.gdt_entries[entry_number].base_low		= (base & 0xFFFF);
	gdt.gdt_entries[entry_number].base_middle	= (base >> 16) & 0xFF;
	gdt.gdt_entries[entry_number].base_high		= (base >> 24) & 0xFF;
	/* Limits */
	gdt.gdt_entries[entry_number].limit_low		= (limit & 0xFFFF);
	gdt.gdt_entries[entry_number].granularity	= (limit >> 16) & 0X0F;
	/* Granularity */
	gdt.gdt_entries[entry_number].granularity	|= (gran & 0xF0);
	/* Access flags */
	gdt.gdt_entries[entry_number].access		= access;
}

void CreateTSSEntry(uint8_t entry_number, uint16_t ss0, uint32_t esp0) {
	tss_entry_t *tss = &gdt.tss_entry;
	uintptr_t base	 = (uintptr_t) tss;
	uintptr_t limit	 = base + sizeof *tss;

	/* Write the TSS entry to the GDT */
	CreateGDTEntry(entry_number, base, limit, 0xE9, 0x00);

	memset(tss, 0x0, sizeof *tss);

	tss->ss0 = ss0;
	tss->esp0 = esp0;
	tss->cs = 0x0b;
	tss->ss = 0x13;
	tss->ds = 0x13;
	tss->es = 0x13;
	tss->fs = 0x13;
	tss->gs = 0x13;

	tss->iomap_base = sizeof *tss;
}

void SetupGDT() {

	gdt_pointer_t *gdt_pointer	= 			  &gdt.gdt_pointer;
	gdt_pointer->limit 		  	= sizeof	   gdt.gdt_entries - 1;
	gdt_pointer->base			= (uintptr_t) &gdt.gdt_entries[0];

	CreateGDTEntry(0, 0, 0, 0, 0);					/* NULL descriptor. */
	CreateGDTEntry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);	/* Kernel code segment. */
	CreateGDTEntry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);	/* Kernel data segment. */
	CreateGDTEntry(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);	/* User code segment. */
	CreateGDTEntry(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);	/* User data segment. */
	CreateTSSEntry(5, 0x10, 0x0);					/* TSS */

	FlushGDT((uintptr_t) gdt_pointer);
	FlushTSS();
}
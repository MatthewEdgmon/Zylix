/**
 * gdt.c - i686 Global Descriptor Table
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

#include "gdt.h"
#include "pic.h"

#define SEG_DATA_RD        0x00 // Read-Only
#define SEG_DATA_RDA       0x01 // Read-Only, accessed
#define SEG_DATA_RDWR      0x02 // Read/Write
#define SEG_DATA_RDWRA     0x03 // Read/Write, accessed
#define SEG_DATA_RDEXPD    0x04 // Read-Only, expand-down
#define SEG_DATA_RDEXPDA   0x05 // Read-Only, expand-down, accessed
#define SEG_DATA_RDWREXPD  0x06 // Read/Write, expand-down
#define SEG_DATA_RDWREXPDA 0x07 // Read/Write, expand-down, accessed
#define SEG_CODE_EX        0x08 // Execute-Only
#define SEG_CODE_EXA       0x09 // Execute-Only, accessed
#define SEG_CODE_EXRD      0x0A // Execute/Read
#define SEG_CODE_EXRDA     0x0B // Execute/Read, accessed
#define SEG_CODE_EXC       0x0C // Execute-Only, conforming
#define SEG_CODE_EXCA      0x0D // Execute-Only, conforming, accessed
#define SEG_CODE_EXRDC     0x0E // Execute/Read, conforming
#define SEG_CODE_EXRDCA    0x0F // Execute/Read, conforming, accessed

extern void LoadGDT(uintptr_t);
extern void StoreGDT(uintptr_t);
extern void LoadTSS(void);

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
    gdt_entry_t     entries[6];
    gdt_pointer_t   pointer;
    tss_entry_t     tss_entry;
} gdt __attribute__((used));

void GDTSetKernelStack(uintptr_t stack) {
    gdt.tss_entry.esp0 = stack;
}

void GDTCreateEntry(uint8_t number, uint64_t base, uint64_t limit, uint8_t access, uint8_t gran) {
    /* Base Address */
    gdt.entries[number].base_low      = (base & 0xFFFF);
    gdt.entries[number].base_middle   = (base >> 16) & 0xFF;
    gdt.entries[number].base_high     = (base >> 24) & 0xFF;
    /* Limits */
    gdt.entries[number].limit_low     = (limit & 0xFFFF);
    gdt.entries[number].granularity   = (limit >> 16) & 0X0F;
    /* Granularity */
    gdt.entries[number].granularity   |= (gran & 0xF0);
    /* Access flags */
    gdt.entries[number].access        = access;
}

static void TSSCreateEntry(uint8_t number, uint16_t ss0, uint32_t esp0) {
    tss_entry_t *tss = &gdt.tss_entry;
    uintptr_t tss_low = (uintptr_t) tss;
    uintptr_t tss_high = (uintptr_t) tss + sizeof *tss;

    /* Write the TSS entry to the GDT */
    GDTCreateEntry(number, tss_low, tss_high, 0xE9, 0x00);

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
    gdt_pointer_t *gdt_pointer  =             &gdt.pointer;
    gdt_pointer->limit          = sizeof       gdt.entries - 1;
    gdt_pointer->base           = (uintptr_t) &gdt.entries[0];

    GDTCreateEntry(0, 0, 0, 0, 0);                  /* NULL descriptor. */
    GDTCreateEntry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);   /* Kernel code segment. */
    GDTCreateEntry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);   /* Kernel data segment. */
    GDTCreateEntry(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);   /* User code segment. */
    GDTCreateEntry(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);   /* User data segment. */
    TSSCreateEntry(5, 0x10, 0x0);                   /* TSS */

    LoadGDT((uintptr_t) gdt_pointer);
    LoadTSS();
}

void VerifyGDT() {
    gdt_pointer_t *stored_gdt = 0;

    StoreGDT((uintptr_t) stored_gdt);
}

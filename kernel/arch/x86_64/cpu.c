/**
 * cpu.c - x86_64 CPU specific startup, management and utilities.
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

#include "x86_64.h"
#include "cpu_info_x86_64.h"
#include "idt.h"
#include "paging.h"
#include "pic.h"
#include "gdt.h"
#include "pit.h"

/**
 * Read the current value of the CPU's time-stamp counter and store into EDX:EAX.
 * The time-stamp counter contains the amount of clock ticks that have elapsed since the last CPU reset.
 * The value is stored in a 64-bit MSR and is incremented after each clock cycle.
 */
uint64_t rdtsc() {
    uint64_t value;
    __asm__ __volatile__("rdtsc" : "=A"(value));
    return value;
}

void FPULoadControlWord(uint16_t control) {
    __asm__ __volatile__("fldcw %0;"::"m"(control));
}

void EnterLongMode() {
    /* Disable paging. */
    /* Set the PAE enable bit in CR4. */
    /* Load CR3 with physical address of PML4. */
    /* Set EFER.LME flag in MSR 0xC0000080 */
    /* Enable paging. */
}

void SetupCPU() {
	StoreCPUInformation();
    SetupGDT();
	SetupIDT();
    SetupISR();
	SetupPIC();
    SetupPIT();
    SetupPaging();

    /* Paging enabled past this point. */

    /* Jump from 32-bit to 64-bit here. */
    EnterLongMode();
}

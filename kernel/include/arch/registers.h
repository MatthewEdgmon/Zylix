/**
 * registers.h - "Cross-platform" header for defining a register structure.
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

#ifndef __REGISTERS_H__
#define __REGISTERS_H__

#include <stdint.h>

#ifdef ARCH_i686

typedef struct cpu_registers {
	unsigned int GS, FS, ES, DS;
	unsigned int EDI, ESI, EBP, ESP, EBX, EDX, ECX, EAX;
	unsigned int interrupt_number, error_code;
	unsigned int EIP, CS, eflags, useresp, SS;
} cpu_registers_t;

#endif

#ifdef ARCH_x86_64

typedef struct cpu_registers {
    /* General Purpose Registers */
    uint64_t rax, rbx, rcx, rdx, rsi, rdi, rsp, rbp;
    /* Pointer Registers. */
    uint64_t rip;
    /* Processor Flags. */
    uint64_t rflags;
    /* x86_64 Specific General Purpose Registers */
    uint64_t r8, r9, r10, r11, r12, r13, r14, r15;
    /* Segment Registers (these are saved for running 32 bit code on 64 bit platforms). */
	uint16_t cs, ds, ss, es, fs, gs;

    /* Variables saved with the registers for IRQ handler. */
	unsigned int interrupt_number, error_code, useresp;
} cpu_registers_t;

#endif

#endif /* __REGISTERS_H__ */

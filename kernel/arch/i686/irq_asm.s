/**
 * irq_asm.s - i686 Interrupt Assembly
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

.code32
.section .text
.align 4

.macro IRQ ident byte
    .global irq\ident
    .type irq\ident, @function
    irq\ident:
        cli
        push $0x00
        push $\byte
        jmp CommonIRQ
.endm

IRQ 0, 32
IRQ 1, 33
IRQ 2, 34
IRQ 3, 35
IRQ 4, 36
IRQ 5, 37
IRQ 6, 38
IRQ 7, 39
IRQ 8, 40
IRQ 9, 41
IRQ 10, 42
IRQ 11, 43
IRQ 12, 44
IRQ 13, 45
IRQ 14, 46
IRQ 15, 47

.extern PICHandlerIRQ
.type PICHandlerIRQ, @function

CommonIRQ:
	# Save all registers.
    push %eax
    push %ecx
    push %edx
    push %ebx
    push %esp
    push %ebp
    push %esi
    push %edi

    # Save segment registers.
    push %ds
    push %es
    push %fs
    push %gs

    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs

    # Call interrupt handler.
    push %esp
    call PICHandlerIRQ
    add $4, %esp

    # Restore segment registers.
    pop %gs
    pop %fs
    pop %es
    pop %ds

    # Restore all registers.
    push %rdi
    push %rsi
    push %rbp
    push %rsp
    push %rbx
    push %rdx
    push %rcx
    push %rax

	# Pop CS, EIP, EFLAGS, SS and ESP
	iret

/**
 * isr_asm.s - i686 ISR assembly
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

.section .text
.align 4

# For defining an interrupt that doesn't push an error code, we push a zero instead.
.macro ISR_NOERROR index
    .global isr\index
    isr\index:
        cli
        push $0
        push $\index
        jmp CommonISR
.endm

# For defining an interrupt that pushes an error code on the stack.
.macro ISR_ERROR index
    .global isr\index
    isr\index:
        cli
        push $\index
        jmp CommonISR
.endm

# CPU dedicated interrupts.
ISR_NOERROR 0
ISR_NOERROR 1
ISR_NOERROR 2
ISR_NOERROR 3
ISR_NOERROR 4
ISR_NOERROR 5
ISR_NOERROR 6
ISR_NOERROR 7
ISR_ERROR   8
ISR_NOERROR 9
ISR_ERROR   10
ISR_ERROR   11
ISR_ERROR   12
ISR_ERROR   13
ISR_ERROR   14
ISR_NOERROR 15
ISR_NOERROR 16
ISR_NOERROR 17
ISR_NOERROR 18
ISR_NOERROR 19
ISR_NOERROR 20
ISR_NOERROR 21
ISR_NOERROR 22
ISR_NOERROR 23
ISR_NOERROR 24
ISR_NOERROR 25
ISR_NOERROR 26
ISR_NOERROR 27
ISR_NOERROR 28
ISR_NOERROR 29
ISR_NOERROR 30
ISR_NOERROR 31
ISR_NOERROR 99

.extern ISRFaultHandler
.type ISRFaultHandler, @function

CommonISR:
    # Push all registers.
    pusha

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

    # Call fault handler.
    push %esp
    call ISRFaultHandler
    add $4, %esp

    # Restore segment registers.
    pop %gs
    pop %fs
    pop %es
    pop %ds

    # Restore all registers.
    popa
    /* Cleanup error code and ISR */
    add $8, %esp
    /* pop CS, EIP, EFLAGS, SS and ESP */
    iret

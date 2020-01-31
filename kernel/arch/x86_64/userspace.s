/**
 * userspace.s - x86_64 Userspace Jump
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

.code64
.section .text
.align 4

.global UserspaceReturn
.type UserspaceReturn, @function

UserspaceReturn:
    # Restore segment registers.
    pop %rdx
    pop %rcx
    pop %rbx
    pop %rax
    mov %gs, %dx
    mov %fs, %cx
    mov %es, %bx
    mov %ds, %ax

    # Restore all registers.
    pop %rdi
    pop %rsi
    pop %rbp
    pop %rsp
    pop %rbx
    pop %rdx
    pop %rcx
    pop %rax

    # Pop CS, EIP, EFLAGS, SS and ESP
    iret

.global UserspaceJump
.type UserspaceJump, @function

UserspaceJump:

    /* Request ring3 */
    or $0x200, %rax
    push %rax
    push $0x1B

    iret
    push %rbp
    ret

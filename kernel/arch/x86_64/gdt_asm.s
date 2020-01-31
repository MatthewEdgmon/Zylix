/**
 * gdt_asm.s - x86_64 Global Descriptor Table assembly.
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

.global LoadGDT
.type LoadGDT, @function

LoadGDT:
    mov 8(%rsp), %rax
    lgdt (%rax)
    ret

/*
TODO: Wrong
ReloadSegments:
    0x10 points to the new data selector.
    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %ss

    ljmp $0x08, $.flush
.flush:
    ret
*/

.global StoreGDT
.type StoreGDT, @function

StoreGDT:
    mov 8(%rsp), %rax
    sgdt (%rax)
    ret

.global LoadTSS
.type LoadTSS, @function

LoadTSS:
    mov $0x2B, %ax
    ltr %ax
    ret

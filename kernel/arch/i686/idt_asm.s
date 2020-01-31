/**
 * idt_asm.s - i686 Interrupt Descriptor Table assembly.
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

.global LoadIDT
.type LoadIDT, @function

# Takes a pointer to the IDT
LoadIDT:
    mov 4(%esp), %eax
    lidt (%eax)
    ret

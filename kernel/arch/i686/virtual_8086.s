/**
 * virtual_8086.s - i686 Virtual 8086 driver
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

.section text
.align 4

.global Virtual8086
.type Virtual8086, @function

Virtual8086:
    cli
    /* We need a 16-bit GDT. */

    /* Save the protected mode cr0. */
    mov %cr0, %eax
    /* Disable paging and enable 16-bit pmode. */
    and $0x7FFFFFFE, %eax
    mov %cr0, %eax

    /* Perform a far jump to set CS. */
    jmp EnterRealMode

EnterRealMode:
    /* Reset segment registers to 0. */
    movw $0, %ax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs
    movw %ax, %ss
    sti

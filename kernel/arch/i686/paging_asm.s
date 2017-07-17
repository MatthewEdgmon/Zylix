/**
 * paging.c - i686 Paging assembly.
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

.global PagingEnable
.type PagingEnable, @function

PagingEnable:
    /* Load cr3 with the address of the page directory. */
    mov 4(%esp), %eax
    mov %cr3, %eax

    /* Set the paging (PG) and protection (PE) bits of cr0. */
    mov %eax, %cr0
    or %eax, 0x80000001
    mov %cr0, %eax
    ret

.global PagingActivatePSE
.type PagingActivatePSE, @function

PagingActivatePSE:
    /* Set the page size extension (PSE) bit of cr4. */
    mov %eax, %cr4
    or %eax, 0x00000010
    mov %cr4, %eax
    ret

.global PagingActivatePAE
.type PagingActivatePAE, @function

PagingActivatePAE:
    /* Set the physical address extension (PAE) bit of cr4. */
    mov %eax, %cr4
    or %eax, 0x00000020
    mov %cr4, %eax
    ret

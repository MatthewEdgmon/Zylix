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

.global PagingLoadCR3
.type PagingLoadCR3, @function

/* Arg 1 - 32-bit pointer to physical address of page directory. */
PagingLoadCR3:
    mov 8(%esp), %eax
    mov %eax, %cr3
    ret

.global PagingEnable
.type PagingEnable, @function

PagingEnable:
    /* Set the paging (PG) bit of cr0. */
    mov %cr0, %eax
    or 0x80000000, %eax
    mov %eax, %cr0
    ret

.global PagingDisable
.type PagingDisable, @function

PagingDisable:
    /* Clear the paging (PG) bit of cr0. */
    mov %cr0, %eax
    or 0x80000000, %eax
    mov %eax, %cr0
    ret

.global PagingActivatePSE
.type PagingActivatePSE, @function

PagingActivatePSE:
    /* Set the page size extension (PSE) bit of cr4. */
    mov %cr4, %eax
    or 0x00000010, %eax
    mov %eax, %cr4
    ret

.global PagingActivatePAE
.type PagingActivatePAE, @function

PagingActivatePAE:
    /* Set the physical address extension (PAE) bit of cr4. */
    mov %cr4, %eax
    or 0x00000020, %eax
    mov %eax, %cr4
    ret

.global PagingActivateLA57
.type PagingActivateLA57, @function

PagingActivateLA57:
    /* Set the LA57 bit in CR4. */
    mov %cr4, %eax
    or 0x00001000, %eax
    mov %eax, %cr4
    ret

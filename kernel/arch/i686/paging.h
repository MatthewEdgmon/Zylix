/**
 * paging.h - i686 Paging
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

#ifndef __PAGING_H__
#define __PAGING_H__

#include <stdint.h>

/**
 * Example of how the Page Directory and Page Table interact.
 *
 * [CR3 Register] > [Page Directory]
 *                         \/
 *                     [PD Entry]
 *                     [PD Entry]
 *                     [PD Entry]    > [Page Table]
 *                                          \/
 *                                      [PT Entry]
 *                                      [PT Entry]
 *                                      [PT Entry]  > [4K/4M Page]
 *
 * Things get even more confusing because in order to dynamically change
 * the page tables and directory the very last page directory entry is a map
 * back to itself. This is because when paging is enabled the processor no
 * longer works with physical address. So PDE #1024 is used as a self reference
 * for the PD.
 */

 #define PAGE_DIRECTORY_BIT_PRESENT       0 /* If set, page is in physical memory. i.e. not cached to disk. */
 #define PAGE_DIRECTORY_BIT_READ_WRITE    1 /* If set, page is writtable, else it is read only. (This applies in userspace only) */
 #define PAGE_DIRECTORY_BIT_USER_SUPER    2 /* If set, access is unprivleged. */
 #define PAGE_DIRECTORY_BIT_WRITE_THROUGH 3 /* If set, write-through caching is enabled, else write-back. */
 #define PAGE_DIRECTORY_BIT_DISABLE_CACHE 4 /* If set, page will not be cached. */
 #define PAGE_DIRECTORY_BIT_ACCESSED      5 /* If set, page has been read/written. */
 #define PAGE_DIRECTORY_BIT_UNUSED0       6
 #define PAGE_DIRECTORY_BIT_SIZE          7
 #define PAGE_DIRECTORY_BIT_GLOBAL        8 /* If set, prevents the TLB from updating the address in its cache if CR3 is reset. */

 #define PAGE_TABLE_BIT_PRESENT           0 /* If set, page is in physical memory. i.e. not cached to disk. */
 #define PAGE_TABLE_BIT_READ_WRITE        1 /* If set, page is writtable, else it is read only. (This applies in userspace only) */
 #define PAGE_TABLE_BIT_USER_SUPER        2 /* If set, access is unprivleged. */
 #define PAGE_TABLE_BIT_WRITE_THROUGH     3 /* If set, write-through caching is enabled, else write-back. */
 #define PAGE_TABLE_BIT_CACHE_DISABLE     4 /* If set, page will not be cached. */
 #define PAGE_TABLE_BIT_ACCESSED          5 /* If set, page has been read/written. */
 #define PAGE_DIRECTORY_BIT_DIRTY         6 /* If set, page has been written. */
 #define PAGE_TABLE_BIT_UNUSED0           7
 #define PAGE_TABLE_BIT_GLOBAL            8 /* If set, prevents the TLB from updating the address in its cache if CR3 is reset. */

uintptr_t PagingGetPhysical(uintptr_t virtual);
void PagingMapPage(uintptr_t physical, uintptr_t virtual, uint16_t flags);

/* Located in paging_asm.s */
void PagingLoadCR3(uint32_t*);
void PagingEnable();
void PagingDisable();
void PagingEnablePSE();
void PagingDisablePSE();
void PagingEnablePAE();
void PagingDisablePAE();
void PagingEnableLA57();
void PagingDisableLA57();

void SetupPaging();

#endif /* __PAGING_H__ */

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
 * back to itself. So PDE #1024 is NOT an actual page table.
 */

/**
 * Bit field structure describing a page.
 */
typedef struct {
    unsigned int present:1;       /* If set, page is in physical memory. i.e. not cached to disk. */
    unsigned int read_write:1;    /* If set, page is writtable, else it is read only. (This applies in userspace only) */
    unsigned int user_super:1;    /* If set, access is unprivleged. */
    unsigned int write_through:1; /* If set, write-through caching is enabled, else write-back. */
    unsigned int cache_disable:1; /* If set, page will not be cached. */
    unsigned int accessed:1;      /* If set, page has been read/written. */
    unsigned int dirty:1;         /* If set, page has been written. */
    unsigned int global:1;        /* If set, prevents the TLB from updating the address in its cache if CR3 is reset. */
    unsigned int reserved:4;
    unsigned int physical_address:20;
} __attribute__((packed)) page_t;

typedef struct {
    page_t pages[1024];
} page_table_t;

typedef struct {
    uintptr_t     physical_tables[1024]; /* Each member of the array is a physical address to the page table. */
    page_table_t* tables[1024];
    uintptr_t     physical_address;      /* Physical address of physical_tables[] */
    int32_t       ref_count;
} page_directory_t;

uintptr_t PagingGetPhysical(uintptr_t virtual);
void PagingMapPage(uintptr_t physical, uintptr_t virtual, uint16_t flags);
void PagingDebugPrintDirectory(page_directory_t* directory);

void SetupPaging();

#endif /* __PAGING_H__ */

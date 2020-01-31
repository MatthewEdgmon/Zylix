/**
 * paging.c - x86_64 Paging
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

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <memory/liballoc.h>

#include "control_registers.h"
#include "cpu_info_x86_64.h"
#include "paging.h"

bool using_pae = false;
bool using_pse = false;

bool paging_active = false;

/**
 * Returns a physical address for a mapped virtual address.
 */
uintptr_t PagingGetPhysical(uintptr_t virtual) {

    uint32_t page_directory_index = (uint32_t) virtual >> 22;
    uint32_t page_table_index = (uint32_t) virtual >> 12 & 0x03FF;

    return NULL;
}

/**
 * Maps a physical address to a virtual address.
 * NOTE: Both address must be page aligned.
 */
void PagingMapPage(uintptr_t physical, uintptr_t virtual, uint16_t flags) {
    /* Ensure both addresses are page aligned. */

    uint32_t page_directory_index = (uint32_t) virtual >> 22;
    uint32_t page_table_index = (uint32_t) virtual >> 12 & 0x03FF;

    /* Flush TLB. */
}

void PagingUpdateFeatures() {

    if(paging_active) {
        return;
    }

    if(cpu_info->features_PAE) {
        using_pae = true;
    }

    if(cpu_info->features_PSE) {
        using_pse = true;
    }
}

void SetupPaging() {

    if(paging_active) {
        return;
    }

    /* Simple paging for now. */
    //PagingUpdateFeatures();

    /* Determine total memory size. */

    /* Setup identity mapping for now. */

    /*


    CR3 now takes PML4, not page directory, fix it.




    */

    uint32_t page_directory[1024] __attribute__((aligned(4096)));

    for(size_t i = 0; i < 1024; i++) {
        page_directory[i] = 0x00000002;
    }

    uint32_t first_page_table[1024] __attribute__((aligned(4096)));

    for(size_t i = 0; i < 1024; i++) {
        first_page_table[i] = (i * 0x1000) | 0x3;
    }

    page_directory[0] = (uint32_t) first_page_table | 3;

    LoadCR3(page_directory);

    /* Change this to LoadCR0 with paging bit enabled. */
    //PagingEnable();

    paging_active = true;
}

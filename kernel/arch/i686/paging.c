/**
 * paging.c - i686 Paging
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

#include "cpu_info_i686.h"
#include "paging.h"

extern void PagingLoadCR3(uint32_t*);
extern void PagingEnable(void);
extern void PagingDisable(void);
extern void PagingActivatePSE(void);
extern void PagingActivatePAE(void);
extern void PagingActivateLA57(void);

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
        PagingActivatePAE();
        using_pae = true;
    }

    if(cpu_info->features_PSE) {
        PagingActivatePSE();
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

    uint32_t page_directory[1024] __attribute__((aligned(4096)));

    for(size_t i = 0; i < 1024; i++) {
        page_directory[i] = 0x00000002;
    }

    uint32_t first_page_table[1024] __attribute__((aligned(4096)));

    for(size_t i = 0; i < 1024; i++) {
        first_page_table[i] = (i * 0x1000) | 0x3;
    }

    page_directory[0] = (uint32_t) first_page_table | 3;

    PagingLoadCR3(page_directory);

    PagingEnable();

    paging_active = true;
}

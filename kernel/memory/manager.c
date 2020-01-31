/**
 * manager.c - Memory manager.
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

#include <stdint.h>

#include <common.h>
#include <multiboot.h>
#include <panic.h>

#include <arch/cpu_info.h>
#include <arch/interrupts.h>
#include <arch/registers.h>

#include <memory/manager.h>

#include <structures/double_list.h>

uint8_t use_pae = 0;

uint32_t page_directory[1024] __attribute__((aligned(4096)));

#define PAGE_SIZE 0x1000
#define PAGE_START 0x100000
#define PAGE_MAX 0x3200000

void* current_page = PAGE_START;

void* ManagerPageAllocate(uint16_t num_pages) {
    if(current_page >= PAGE_MAX);
    unsigned int size = num_pages * PAGE_SIZE;
    current_page = current_page + size;
    return current_page;
}

int ManagerPageFree(void* address, uint16_t num_pages) {
    unsigned int size = num_pages * PAGE_SIZE;
    memset(address, NULL, size);
    return 0;
}

/**
 * Takes a physical page and maps it to a returned virtual
 * address.
 */
void* ManagerPageMap(void* physical_address, void* virtual_address, uint32_t flags) {

    uint64_t page_directory_index = (uint64_t) virtual_address >> 22;
    uint64_t page_table_index     = (uint64_t) virtual_address >> 12 & 0x03FF;

}

int ManagerHandlePageFault(cpu_registers_t* registers) {
    return;
}

void SetupMemoryManager(multiboot_info_t* multiboot_info) {

    ISRInstallHandler(ISR_PAGE_FAULT, ManagerHandlePageFault);

    if(cpu_info->features_PAE) {
        use_pae = 1;
    }

    memory_list = DoubleListCreate();

    if(!BIT_CHECK(multiboot_info->flags, 6)) {
        KernelPanic("Memory manager got no memory map!", NULL);
    }

    return;
}

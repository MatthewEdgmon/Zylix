/**
 * manager.h - Memory manager.
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

#ifndef __MANAGER_H__
#define __MANAGER_H__

#include <stdint.h>

#include <arch/registers.h>
#include <structures/double_list.h>
#include <multiboot.h>

double_list_t* memory_list;

void* ManagerPageAllocate(uint16_t num_pages);
int ManagerPageFree(void* address, uint16_t num_pages);

void* ManagerPageMap(void* physical_address, void* virtual_address, uint32_t flags);

int ManagerHandlePageFault(cpu_registers_t* registers);

void SetupMemoryManager(multiboot_info_t* multiboot_info);

#endif /* __MANAGER_H__ */

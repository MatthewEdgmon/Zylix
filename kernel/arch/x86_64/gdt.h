/**
 * gdt.h - i686 Global Descriptor Table
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

#ifndef __GDT_H__
#define __GDT_H__

#include <stdint.h>

void GDTSetKernelStack(uintptr_t stack);
void GDTCreateEntry(uint8_t entry_number, uint64_t base, uint64_t limit, uint8_t access, uint8_t gran);
static void TSSCreateEntry(uint8_t entry_number, uint16_t ss0, uint32_t esp0);

void SetupGDT();

#endif /* __GDT_H__ */

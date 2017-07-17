/**
 * idt.h - i686 Interrupt Descriptor Table management.
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

#ifndef __IDT_H__
#define __IDT_H__

#include <stdint.h>

typedef void (*idt_gate_t)(void);

void IDTCreateEntry(uint8_t entry_number, idt_gate_t base, uint16_t sel, uint8_t flags);

void SetupIDT();

#endif /* __IDT_H__ */

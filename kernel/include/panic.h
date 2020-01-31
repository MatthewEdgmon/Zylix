/**
 * panic.h - Kernel panic.
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

#ifndef __PANIC_H__
#define __PANIC_H__

#include <arch/registers.h>

void _KernelPanic(char* message, const char* file, int line, cpu_registers_t* registers);
void _AssertFailure(const char* statement, const char* file, int line);

#define KernelPanic(message, registers) _KernelPanic(message, __FILE__, __LINE__, registers)
#define Assert(statement) ((statement) ? (void) 0 : _AssertFailure(#statement, __FILE__, __LINE__))

#endif /* __PANIC_H__ */

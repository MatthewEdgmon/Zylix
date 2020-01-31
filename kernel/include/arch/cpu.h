/**
 * cpu.h - CPU specific support code. Cross-platform header.
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

#ifndef __CPU_H__
#define __CPU_H__

#include <stdint.h>

uint64_t rdtsc();

void SetupCPU();
void SetupFPU();

#ifdef ARCH_i686
#include "../../arch/i686/i686.h"
#endif

#ifdef ARCH_x86_64
#include "../../arch/x86_64/x86_64.h"
#endif

#endif /* __CPU_H__ */

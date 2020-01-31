/**
 * cpu_infoh.h - Architecture independent CPU feature management.
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

#ifndef __CPU_INFO_H__
#define __CPU_INFO_H__

#include <stdbool.h>

#ifdef ARCH_i686
#include "../../arch/i686/cpu_info_i686.h"
#endif

#ifdef ARCH_x86_64
#include "../../arch/x86_64/cpu_info_x86_64.h"
#endif

#endif /* __CPU_INFO_H__ */

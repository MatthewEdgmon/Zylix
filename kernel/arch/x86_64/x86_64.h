/**
 * x86_64.h - x86_64 Definitions
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

#ifndef __X86_64_H__
#define __X86_64_H__

#define SYSCALL_VECTOR 0x63

#define USER_STACK_BOTTOM 0xAFF00000
#define USER_STACK_TOP    0xB0000000

#endif /* __X86_64_H__ */

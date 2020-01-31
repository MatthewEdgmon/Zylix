/**
 * syscalls.h - Platform-indepedent glue syscall setup.
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

#ifndef __SYSCALLS_H__
#define __SYSCALLS_H__

#define SYSCALL_EXIT      0
#define SYSCALL_FORK      1
#define SYSCALL_OPEN      2
#define SYSCALL_CLOSE     3
#define SYSCALL_READ      4
#define SYSCALL_WRITE     5
#define SYSCALL_MALLOC    6
#define SYSCALL_FREE      7
#define SYSCALL_GETSTDIN  10
#define SYSCALL_GETSTDOUT 11
#define SYSCALL_GETSTDERR 12
#define SYSCALL_LSEEK     19
#define SYSCALL_GETPID    20
#define SYSCALL_MOUNT     21
#define SYSCALL_UMOUNT    22
#define SYSCALL_REBOOT    23
#define SYSCALL_SYNC      24

/* Located in $(ARCH)/syscalls.c */
void SetupSyscalls();

#endif /* __SYSCALLS_H__ */

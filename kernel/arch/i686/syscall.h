/**
 * syscall.h - i686-specific syscall handling.
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

#ifndef __SYSCALL_H__
#define __SYSCALL_H__

#include <stdint.h>
#include <stdio.h>
#include <stddef.h>

#include <arch/registers.h>

void SyscallHandler(cpu_registers_t* registers);

uint32_t syscall_exit();
uint32_t syscall_fork();
uint32_t getpid();
char** get_env();

uint32_t write(FILE fid, char* buffer, size_t length);
uint32_t read(FILE fid, char* buffer, size_t length);
uint32_t close(FILE fid);
FILE open(char* path, uint32_t offset);
int sys_wait(int pid, int* status, int options);

uint32_t _exit(cpu_registers_t* regs);

#endif /* __SYSCALL_H__ */

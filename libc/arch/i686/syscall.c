/**
 * syscall.c - i686 syscalls for Zylix.
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

#include <syscall.h>
#include <stdint.h>

int syscall_0arg(uint32_t call_no){
	int return_value;
	__asm__ __volatile__ ("movl %0, %%eax" :: "b" (call_no));
	__asm__ __volatile__ ("int $0x63");
	__asm__ __volatile__ ("movl %%eax, %0" : "=r" (return_value));
	return return_value;
}

int syscall_1arg(uint32_t call_no, uint32_t arg1){
	int return_value;
	__asm__ __volatile__ ("movl %0, %%ebx" :: "c" (arg1));
	__asm__ __volatile__ ("movl %0, %%eax" :: "c" (call_no));
	__asm__ __volatile__ ("int $0x63");
	__asm__ __volatile__ ("movl %%eax, %0" : "=r" (return_value));
	return return_value;
}

int syscall_2arg(uint32_t call_no, uint32_t arg1, uint32_t arg2){
	int return_value;
	__asm__ __volatile__ ("movl %0, %%ecx" :: "d" (arg2));
	__asm__ __volatile__ ("movl %0, %%ebx" :: "d" (arg1));
	__asm__ __volatile__ ("movl %0, %%eax" :: "d" (call_no));
	__asm__ __volatile__ ("int $0x63");
	__asm__ __volatile__ ("movl %%eax, %0" : "=r" (return_value));
	return return_value;
}

int syscall_3arg(uint32_t call_no, uint32_t arg1, uint32_t arg2, uint32_t arg3){
	int return_value;
	__asm__ __volatile__ ("movl %0, %%eax" :: "d" (call_no));
	__asm__ __volatile__ ("pushl %eax");
	__asm__ __volatile__ ("movl %0, %%edx" :: "a" (arg3));
	__asm__ __volatile__ ("movl %0, %%ecx" :: "a" (arg2));
	__asm__ __volatile__ ("movl %0, %%ebx" :: "a" (arg1));
	__asm__ __volatile__ ("popl %eax");
	__asm__ __volatile__ ("int $0x63");
	__asm__ __volatile__ ("movl %%eax, %0" : "=r" (return_value));
	return return_value;
}

int syscall_4arg(uint32_t call_no, uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4){
	int return_value;
	__asm__ __volatile__ ("movl %0, %%eax" :: "d" (call_no));
	__asm__ __volatile__ ("pushl %eax");
	__asm__ __volatile__ ("movl %0, %%esi" :: "a" (arg4));
	__asm__ __volatile__ ("movl %0, %%edx" :: "a" (arg3));
	__asm__ __volatile__ ("movl %0, %%ecx" :: "a" (arg2));
	__asm__ __volatile__ ("movl %0, %%ebx" :: "a" (arg1));
	__asm__ __volatile__ ("popl %eax");
	__asm__ __volatile__ ("int $0x63");
	__asm__ __volatile__ ("movl %%eax, %0" : "=r" (return_value));
	return return_value;
}

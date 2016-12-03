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

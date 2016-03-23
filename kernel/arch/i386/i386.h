#ifndef __I386_H__
#define __I386_H__

/**
 * Collection of variables, defines, and functions not visible globally, only for this arch.
 */

#include <libc/stdint.h>

#define SYSCALL_VECTOR 0x90

#define USER_STACK_BOTTOM 0xAFF00000
#define USER_STACK_TOP    0xB0000000

/* CPUInfo.c */
void StoreCPUInformation(void);

/* IRQ.c */
void RemapIRQ();
void SetupIRQ();

#endif /* __I386_H__ */

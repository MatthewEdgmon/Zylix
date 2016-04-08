#ifndef __I386_H__
#define __I386_H__

/**
 * Collection of variables, defines, and functions not visible globally, only for this arch.
 */

#include <libc/stdint.h>

// 99 in base 10
#define SYSCALL_VECTOR 0x63

#define USER_STACK_BOTTOM 0xAFF00000
#define USER_STACK_TOP    0xB0000000

#endif /* __I386_H__ */

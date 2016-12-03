#include <stdint.h>
#include <stdlib.h>

#include <panic.h>

// TODO: Make STACK_CHK_GUARD random at each bootup, different value for each
// physical CPU?

#if UINT32_MAX == UINTPTR_MAX
#define STACK_CHK_GUARD 0xE2DEE396
#else
#define STACK_CHK_GUARD 0x595E9FBD94FDA766
#endif

uintptr_t __stack_chk_guard = STACK_CHK_GUARD;

__attribute__((__noreturn__))
void __stack_chk_fail(void) {
    KernelPanic("Stack smash detected.", NULL);
    while(1);
}

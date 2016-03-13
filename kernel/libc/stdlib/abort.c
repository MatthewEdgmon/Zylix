#include <libc/stdio.h>
#include <libc/stdlib.h>

#include <error.h>

__attribute__((__noreturn__))
void abort(void) {
    KernelPanic("Kernel Panic: abort()\n");
    while(1) { }
    __builtin_unreachable();
}

#include <stdlib.h>
#include <syscall.h>

void free(void* address) {
    (void) syscall_1arg(SYSCALL_FREE, (uint32_t) address);
    return;
}

#include <stdlib.h>
#include <syscall.h>

void* malloc(size_t size) {
    return (void*) syscall_1arg(SYSCALL_MALLOC, size);
}

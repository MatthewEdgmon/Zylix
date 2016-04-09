#include <unistd.h>
#include <syscall.h>
#include <stddef.h>

int write(int fd, void* buffer, size_t count) {
    return syscall_3arg(SYSCALL_WRITE, (uint32_t) fd, (uint32_t) buffer, (uint32_t) count);
}

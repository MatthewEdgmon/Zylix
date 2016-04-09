#include <unistd.h>
#include <syscall.h>
#include <stdint.h>
#include <stddef.h>

int read(int fd, void* buffer, size_t length) {
    return syscall_3arg(SYSCALL_READ, (uint32_t) fd, (uint32_t) buffer, (uint32_t) length);
}

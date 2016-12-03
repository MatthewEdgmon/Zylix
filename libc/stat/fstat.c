#include <stdint.h>
#include <sys/stat.h>
#include <syscall.h>

int fstat(int fd, struct stat* st) {
    return syscall_2arg(SYSCALL_FSTAT, fd, st);
}

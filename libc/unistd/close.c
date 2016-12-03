#include <unistd.h>
#include <errno.h>
#include <syscall.h>

int close(int fd) {
    int r = syscall_1arg(SYSCALL_CLOSE, fd);
    return r;
}

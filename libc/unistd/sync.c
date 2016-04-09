#include <unistd.h>
#include <syscall.h>

void sync() {
    (void) syscall_0arg(SYSCALL_SYNC);
}

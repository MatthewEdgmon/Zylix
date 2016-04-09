#include <unistd.h>
#include <syscall.h>

void _exit(int status) {
    (void) syscall_1arg(SYSCALL_EXIT, (uint32_t) status);
    for(;;);
}

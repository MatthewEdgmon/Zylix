#include <unistd.h>
#include <syscall.h>

int fork() {
	return syscall_0arg(SYSCALL_FORK);
}

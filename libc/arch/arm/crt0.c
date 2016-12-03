#include <syscall.h>
#include <stdio.h>

/* This crt0 is used by userspace programs only. */

FILE* stdin   = NULL;
FILE* stdout  = NULL;
FILE* stderr  = NULL;

#ifdef ZYLIX_LIBC_USERSPACE

extern int main(char** argc, int argv);
extern void _exit(int);

void _start() {
    stdin = (FILE*) syscall_0arg(SYSCALL_GETSTDIN);
	stdout = (FILE*) syscall_0arg(SYSCALL_GETSTDOUT);
	stderr = (FILE*) syscall_0arg(SYSCALL_GETSTDERR);
	_exit(main(NULL, NULL));
}

#endif /* ZYLIX_LIBC_USERSPACE */

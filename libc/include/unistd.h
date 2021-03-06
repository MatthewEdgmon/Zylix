#ifndef __UNISTD_H__
#define __UNISTD_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
#define NULL 0L
#else
#define NULL ((void*)0)
#endif

typedef int pid_t;

#define STDIN_FILENO  0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

#define F_OK 0
#define R_OK 4
#define W_OK 2
#define X_OK 1

#define _POSIX_VERSION       200809L
#define _POSIX2_VERSION      200809L

#define _XOPEN_VERSION       700
#define _XOPEN_UNIX          0

int execv (const char*, char* const[]);
int execve(const char*, char* const[], char* const[]);
int execvp(const char*, char* const[]);

int fork(void);

int read(int, void*, size_t);
void sync();
int write(int, void*, size_t);

#ifdef __cplusplus
}
#endif

#endif /* __UNISTD_H__ */

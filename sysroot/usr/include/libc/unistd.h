#ifndef __UNISTD_H__
#define __UNISTD_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define _POSIX_VERSION 200809L
#define _POSIX2_VERSION 200809L
#define _XOPEN_VERSION 700

#ifdef __cplusplus
#define NULL 0L
#else
#define NULL ((void*)0)
#endif

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

int fork();

#ifdef __cplusplus
}
#endif

#endif /* __UNISTD_H__ */

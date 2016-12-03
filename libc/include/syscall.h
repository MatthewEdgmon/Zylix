#ifndef __SYSCALL_H__
#define __SYSCALL_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SYSCALL_EXIT      0
#define SYSCALL_FORK      1
#define SYSCALL_OPEN      2
#define SYSCALL_CLOSE     3
#define SYSCALL_READ      4
#define SYSCALL_WRITE     5
#define SYSCALL_MALLOC    6
#define SYSCALL_FREE      7
#define SYSCALL_GETSTDIN  10
#define SYSCALL_GETSTDOUT 11
#define SYSCALL_GETSTDERR 12
#define SYSCALL_FSTAT     18
#define SYSCALL_LSEEK     19
#define SYSCALL_GETPID    20
#define SYSCALL_MOUNT     21
#define SYSCALL_UMOUNT    22
#define SYSCALL_REBOOT    23
#define SYSCALL_SYNC      24

int syscall_0arg(uint32_t call_no);
int syscall_1arg(uint32_t call_no, uint32_t arg1);
int syscall_2arg(uint32_t call_no, uint32_t arg1, uint32_t arg2);
int syscall_3arg(uint32_t call_no, uint32_t arg1, uint32_t arg2, uint32_t arg3);
int syscall_4arg(uint32_t call_no, uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4);

#ifdef __cplusplus
}
#endif

#endif /* __SYSCALL_H__ */

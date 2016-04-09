#ifndef __PROCESS_H__
#define __PROCESS_H__

#include <stdint.h>

typedef enum  {
    SLEEPING,
    AWAKE
} process_state_t;

typedef struct process {
    char* name;

    uint32_t pid;
    uint32_t gid;

    process_state_t state;

    uint32_t stdin;
    uint32_t stdout;
    uint32_t stderr;

} process_t;

void ProcessKill(uint32_t pid);

uint32_t ProcessMakeEmpty();

void SetupMultiProcess();

#endif /* __PROCESS_H__ */

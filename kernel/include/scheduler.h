#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

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

void SchedulerKillProcess(uint32_t pid);
uint32_t SchedulerGetCurrentProcess();
uint32_t SchedulerMakeEmptyProcess();

void SetupScheduler();

#endif /* __SCHEDULER_H__*/

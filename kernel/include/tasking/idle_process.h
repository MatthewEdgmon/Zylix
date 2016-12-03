#ifndef __IDLE_PROCESS_H__
#define __IDLE_PROCESS_H__

#include <tasking/process.h>

static void IdleProcessFunction();

process_t* IdleProcessCreate();

#endif /* __IDLE_PROCESS_H__ */

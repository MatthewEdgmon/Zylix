#ifndef __MONITOR_H__
#define __MONITOR_H__

#include <arch/io.h>
#include <arch/interrupts.h>

int RAMMonitorHandler(registers_t* registers);
int RAMMonitorMain();

#endif /* __MONITOR_H__ */

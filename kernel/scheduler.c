#include <stdio.h>
#include <stdint.h>

#include <arch/interrupts.h>
#include <arch/registers.h>

#include <scheduler.h>

process_t* root_process;
process_t* current_process = NULL;

uint32_t SchedulerGetCurrentProcess() {
    return current_process->pid;
}

uint32_t SchedulerMakeEmptyProcess() {
    return 0;
}

void SchedulerTaskSwitch(registers_t registers) {

}

void SetupScheduler() {

}

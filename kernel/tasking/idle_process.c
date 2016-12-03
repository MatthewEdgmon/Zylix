#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <arch/interrupts.h>

#include <tasking/process.h>
#include <tasking/idle_process.h>

static void IdleProcessFunction() {
    while(1) {
        InterruptsEnable();
    }
}

process_t* IdleProcessCreate() {
    process_t* idle = malloc(sizeof(process_t));
    memset(idle, 0x00, sizeof(process_t));

	idle->id = -1;
	idle->name = strdup("System Idle");
    idle->description = strdup("Execution is in this process when system is idle.");
	idle->is_tasklet = 1;

    idle->image.stack = (uintptr_t)malloc(KERNEL_STACK_SIZE) + KERNEL_STACK_SIZE;
	idle->thread.eip  = (uintptr_t)&IdleProcessFunction;
	idle->thread.esp  = idle->image.stack;
	idle->thread.ebp  = idle->image.stack;

    //idle->started = 1;
	//idle->running = 1;
	//idle->wait_queue = list_create();
	//idle->shm_mappings = list_create();
	//idle->signal_queue = list_create();

	//set_process_environment(idle, current_directory);
	return idle;
}

/**
 * multitask.c - Multi-tasking.
 *
 * This file is part of Zylix.
 *
 * Zylix is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Zylix is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Zylix.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <arch/interrupts.h>

#include <tasking/multitask.h>

#include <structures/double_list.h>
#include <structures/tree.h>

static uint32_t next_pid = 1;

bool task_switching = false;

task_t kernel_task = {
    .name        = "/boot/zykernel",
    .pid         = 0,
    .task_type   = TASK_TYPE_SPECIAL,

    .owned_tasks = 0,
    .parent      = 0
};

#define PUSH(stack, type, item) stack -= sizeof(type); *((type *) stack) = item

extern void UserspaceJump(uintptr_t location, uintptr_t stack);

/**
 * Enter ring 3 and jump to the address.
 * TODO: x86 dependent task switching.
 */
void ProcessUserspaceJump(uintptr_t address, int argc, char** argv, uintptr_t stack) {
    // InterruptsDisable();
    // // Save the kernel stack in the GDT.
    // GDTSetKernelStack(current_process->image.stack);
    // // Send the arguments to userspace.
    // PUSH(stack, uintptr_t, (uintptr_t) argv);
    // // Send the argument count to userspace.
    // PUSH(stack, int, argc);
    // UserspaceJump(address, stack);
}

uint32_t GetNewPID() {
    next_pid++;
    return (next_pid - 1);
}

void MultitaskCreateTask() {

}

void MultitaskKillTask(task_t* task) {

    /* Disallow the scheduler to task switch while a task is being killed. */
    task_switching = false;

    /* Check for special cases like killing the kernel or idle process. */
    if(task->task_type == TASK_TYPE_SPECIAL) {
        if(task->pid == 0) {
            printf("Tried to kill kernel!\n");
            return;
        }
    }

    /* If the current executing task is the one being killed, context switch to new one. */

    /* Re-enable task switching now that everything is back in order. */
    task_switching = true;
}

int SetupMultitask() {

    task_list = DoubleListCreate();

    InterruptsDisable();

    DoubleListAppendValue(task_list, &kernel_task);

    InterruptsEnable();

    return 0;
}

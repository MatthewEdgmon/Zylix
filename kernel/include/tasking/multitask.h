/**
 * multitask.h - Multi-tasking.
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

#ifndef __MULTITASK_H__
#define __MULTITASK_H__

#include <stdint.h>

#include <structures/double_list.h>

#define KERNEL_STACK_SIZE 0x8000

double_list_t* task_list;

typedef enum task_type {
    TASK_TYPE_PROCESS,   // Discrete process.
    TASK_TYPE_THREAD,    // Thread owned by a process.
    TASK_TYPE_SPECIAL    // Virtual 8086 task, kernel, idle, etc.
} task_type_t;

typedef struct task {
    char           name[32];         // Task's name.
    uint32_t       pid;              // Process ID
    task_type_t    task_type;        // Task type (process or thread).

    double_list_t* owned_tasks;      // All tasks owned by this task.
    struct task_t* parent;           // Owner of this task, if thread.

} __attribute__((__packed__)) task_t;

void ProcessUserspaceJump(uintptr_t address, int argc, char** argv, uintptr_t stack);

uint32_t MultitaskGetNewPID();

void MultitaskCreateTask();
void MultitaskKillTask();

int SetupMultitask();

#endif /* __MULTITASK_H__ */

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <arch/interrupts.h>

#include <tasking/process.h>
#include <tasking/idle_process.h>
#include <tasking/init_process.h>
#include <tasking/test_process.h>

#include <structures/list.h>
#include <structures/tree.h>

#define PUSH(stack, type, item) stack -= sizeof(type); *((type *) stack) = item

char* process_default_name = "[Unamed Process]";

void GenerateProcessTree() {
    process_tree = TreeCreate();
    process_list = ListCreate();
    process_queue = ListCreate();
    sleep_queue = ListCreate();
}

extern void UserspaceJump(uintptr_t location, uintptr_t stack);

/**
 * Enter ring 3 and jump to the address.
 * TODO: x86 dependent task switching.
 */
void ProcessUserspaceJump(uintptr_t address, int argc, char** argv, uintptr_t stack) {
    InterruptsDisable();
    // Save the kernel stack in the GDT.
    GDTSetKernelStack(current_process->image.stack);
    // Send the arguments to userspace.
    PUSH(stack, uintptr_t, (uintptr_t) argv);
    // Send the argument count to userspace.
    PUSH(stack, int, argc);
    UserspaceJump(address, stack);
}

process_t* ProcessCreate() {
	if(process_tree->root_node == NULL) {
		printf("Tried to create a process with no root process in tree.\n");
		printf("Process not created.\n");
		return NULL;
	}

	process_t* new_process = calloc(sizeof(process_t), 1);
}

void SetupProcessing() {
    InterruptsDisable();

    GenerateProcessTree();

    current_process = InitProcessCreate();

	/* Set the init process as the top of the process tree. */
    TreeSetRoot(process_tree, (void*) current_process);

	/* Set the init process as the start of the process list. */
    ListAppendNode(process_list, (void*) current_process);

    idle_process = IdleProcessCreate();

    InterruptsEnable();
}

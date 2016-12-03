#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <arch/interrupts.h>

#include <tasking/process.h>
#include <tasking/init_process.h>

process_t* InitProcessCreate() {
    if(process_tree->root_node == NULL) {
		printf("Tried to recreate the init process.\n");
		return NULL;
	}

    process_t* init = malloc(sizeof(process_t));
    memset(init, 0x00, sizeof(process_t));

    /* Begin filling out the init process structure. */
    init->id                 = 1;
    init->name               = strdup("init");
    init->description        = strdup("The initial process spawned.");
    init->user               = 0;
    init->mask               = 022;
    init->command_line       = NULL;
    init->finished           = 0;
    init->started            = 1;
    init->running            = 1;
    init->wait_queue         = ListCreate();
    init->shm_mappings       = ListCreate(); /* Shared memory chunk mappings. */
    init->signal_queue       = ListCreate(); /* Queued signals. */
    init->is_tasklet         = 0;
    return init;
}

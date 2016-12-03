#ifndef __PROCESS_H__
#define __PROCESS_H__

#include <stdint.h>

#include <arch/registers.h>

#include <structures/tree.h>
#include <structures/list.h>

#define KERNEL_STACK_SIZE 0x8000

typedef signed int     pid_t;
typedef unsigned int   user_t;
typedef unsigned char  status_t;

typedef void (*tasklet_t) (void *, char *);

typedef struct thread {
    uintptr_t  esp; /* Stack Pointer */
	uintptr_t  ebp; /* Base Pointer */
	uintptr_t  eip; /* Instruction Pointer */

	uint8_t    fpu_enabled;
	uint8_t    fp_regs[512];

	uint8_t    padding[32]; /* I don't know */
} thread_t;

typedef struct image {
    size_t        size;              /* Image size */
    uintptr_t     entry;             /* Binary entry point */
    uintptr_t     heap;              /* Heap pointer */
    uintptr_t     heap_actual;       /* Actual heap location */
    uintptr_t     stack;             /* Process kernel stack */
    uintptr_t     user_stack;        /* User stack */
    uintptr_t     start;
    uintptr_t     shm_heap;
	volatile int lock[2];
} image_t;

typedef struct process {
    pid_t         id;                /* Process ID. */
    char*         name;              /* Process name. */
    char*         description;       /* Process description. */
    user_t        user;              /* Effetive user. */
    int           mask;              /* User mask. */

    char**        command_line;      /* Self explanatory. */

    pid_t         group;             /* Process thread group */
    pid_t         job;               /* Process job group */
    pid_t         session;           /* Session group */

    thread_t      thread;            /* Associated task information */
	tree_node_t*  tree_entry;        /* Process Tree entry */
    list_node_t*  list_entry;        /* Process List entry. */
    image_t       image;             /* Binary image information */
//  fs_node_t     working_dir_node;  /* Node of the working directory. */
    char*         working_dir_name;  /* Full name of the working directory. */
    uint8_t       finished;          /* Non-zero if finished. */
    uint8_t       started;           /* Non-zero if started. */
    uint8_t       running;           /* Non-zero if running. */
    registers_t*  registers;         /* Registers at interrupt. */
    list_t*       wait_queue;
    list_t*       shm_mappings;      /* Shared memory chunk mappings. */
    list_t*       signal_queue;      /* Queued signals. */
    uint8_t       is_tasklet;        /* Non-zero if tasklet. */
} process_t;

tree_t * process_tree;  /* Parent->Children tree */
list_t * process_list;  /* Flat storage */
list_t * process_queue; /* Ready queue */
list_t * sleep_queue;

process_t* root_process;
process_t* current_process;
process_t* idle_process;

void GenerateProcessTree();

static void ProcessKernelIdleFunction();
process_t* ProcessCreateIdleProcess();
process_t* ProcessCreateInitProcess();
void ProcessUserspaceJump(uintptr_t address, int argc, char** argv, uintptr_t stack);
void SetupProcessing();

#endif /* __PROCESS_H__ */

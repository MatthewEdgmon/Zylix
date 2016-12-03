#include <stdint.h>
#include <stdio.h>

#include <tasking/elf.h>
#include <tasking/execute.h>

#include <terminal.h>

/**
 * Functions for executing a program from a file or other medium. This is NOT the
 * same as creating a new process.
 */

int ExecuteELF() {
    /* Read the file from memory. */
    /* Process the header. */
    /* Determine if it's a valid ELF, else return. */
    /* Allocate memory for the program. */
    /* Place it's code at the entry point. */
    /* Close the file. */
    /* Fork to new PID. */
    /* Get the return code and return that to Execute() */
    return 0;
}

int ExecuteShebang() {
    /* Get the return code and return that to Execute() */
    return 0;
}

int Execute(char* path) {
    /* Determine file type. */
    /* Execute it. */
    return 0;
}

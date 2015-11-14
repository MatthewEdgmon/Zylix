/**
 * ELF Loader.
 */
#include <execute.h>

#include <common.h>
#include <types.h>

#include <terminal.h>

/* Executable types. */
#include <elf.h>

/**
 * Execute an elf binary.
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

/**
 * Execute a script shebang.
 */
int ExecuteShebang() {
    /* Get the return code and return that to Execute() */
    return 0;
}

/**
 * Execute something.
 */
int Execute() {
    /* Determine file type. */
    /* Execute it. */
    return 0;
}
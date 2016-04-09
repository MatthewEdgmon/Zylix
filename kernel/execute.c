#include <stdint.h>
#include <stdio.h>

#include <execute.h>

#include <terminal.h>

/* Executable types. */
#include <elf.h>

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

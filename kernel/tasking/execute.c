/**
 * execute.c - Load a program into memory and start it.
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

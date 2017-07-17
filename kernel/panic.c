/**
 * panic.c - Kernel panic handler.
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

#include <arch/interrupts.h>
#include <arch/registers.h>
#include <arch/stop.h>

#include <devices/video/vga.h>

#include <panic.h>
#include <terminal.h>

void _KernelPanic(char* message, const char* file, int line, registers_t* registers) {
    InterruptsDisable();
    TerminalClear();
    TerminalSetColor(TerminalMakeColor(COLOR_LIGHT_RED, COLOR_BLACK));
    printf("Kernel panic!\n");
    printf("  Message: %s\n", message);
    printf("     File: %s\n", file);
    printf("     Line: %d\n", line);
    if(registers) {
        printf("\nRegisters:\n");
        printf("EAX=0x%X EBX=0x%X\n", registers->EAX, registers->EBX);
        printf("ECX=0x%X EDX=0x%X\n", registers->ECX, registers->EDX);
        printf("ESP=0x%X EBP=0x%X\n", registers->ESP, registers->EBP);
        printf("         EIP=0x%X\n", registers->EIP);
        printf("Error code:  0x%X\n", registers->error_code);
        printf("EFLAGS:      0x%X\n", registers->eflags);
        printf("User ESP:    0x%X\n", registers->useresp);
    }
    printf("\nStopping execution.\n");
    while(1) {
        stop_execution();
    }
}

void _AssertFailure(const char* statement, const char* file, int line) {
    InterruptsDisable();
    TerminalClear();
    TerminalSetColor(TerminalMakeColor(COLOR_LIGHT_RED, COLOR_BLACK));
    printf("Kernel assertation failure!\n");
    printf("Statement: %s\n", statement);
    printf("     File: %s\n", file);
    printf("     Line: %d\n", line);
    printf("\nStopping execution.\n");
    while(1) {
        stop_execution();
    }
}

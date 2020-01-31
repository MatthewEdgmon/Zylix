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

void _KernelPanic(char* message, const char* file, int line, cpu_registers_t* registers) {
    InterruptsDisable();
    TerminalClear();
    TerminalSetColor(TerminalMakeColor(COLOR_LIGHT_RED, COLOR_BLACK));
    printf("Kernel panic!\n");
    printf("  Message: %s\n", message);
    printf("     File: %s\n", file);
    printf("     Line: %d\n", line);

#ifdef ARCH_x86_64
    if(registers) {
        printf("\nRegisters:\n");
        printf("RAX=0x%X RBX=0x%X RCX=0x%X RDX=0x%X\n", registers->rax, registers->rbx, registers->rcx, registers->rdx);
        printf("RSI=0x%X RDI=0x%X RSP=0x%X RBP=0x%X\n", registers->rsi, registers->rdi, registers->rsp, registers->rbp);
        printf("R8 =0x%X R9 =0x%X R10=0x%X R11=0x%X\n", registers->r8,  registers->r9,  registers->r10, registers->r11);
        printf("R12=0x%X R13=0x%X R14=0x%X R15=0x%X\n", registers->r12, registers->r13, registers->r14, registers->r15);
        printf("         RIP=0x%X\n", registers->rip);
        printf("Error code:  0x%X\n", registers->error_code);
        printf("RFLAGS:      0x%X\n", registers->rflags);
        printf("User ESP:    0x%X\n", registers->useresp);
    }
#endif

#ifdef ARCH_i686
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
#endif

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

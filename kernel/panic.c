#include <stdint.h>
#include <stdio.h>

#include <arch/interrupts.h>
#include <arch/registers.h>
#include <arch/stop.h>

#include <devices/vga.h>

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

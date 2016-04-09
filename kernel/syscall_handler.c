#include <stdio.h>

#include <arch/interrupts.h>
#include <arch/registers.h>

#include <devices/ps2keyboard.h>

#include <filesystem/file.h>

#include <syscall_handler.h>

#include <terminal.h>

void SyscallHandler(registers_t* registers) {
    switch(registers->EAX) {
        /* No arguments. */
        case SYSCALL_FORK:
            registers->EAX = fork(registers);
            return;
        case SYSCALL_GETSTDIN:
        case SYSCALL_GETSTDOUT:
        case SYSCALL_GETSTDERR:
            return;
        case SYSCALL_SYNC:
            return;
        /* 2 arguments. */
        case SYSCALL_CLOSE:
            return;
        case SYSCALL_OPEN:
            registers->EAX = open((char*) registers->EBX, registers->ECX);
            return;
        /* 3 arguments. */
        case SYSCALL_WRITE:
            registers->EAX = write(registers->EBX, (char*) registers->ECX, (size_t) registers->EDX);
            return;
        case SYSCALL_READ:
            registers->EAX = read(registers->EBX, (char*) registers->ECX, (size_t) registers->EDX);
            return;

        default:
            printf("Unhandled syscall.\n");
            return;
    }
    return;
}

uint32_t fork(registers_t* registers) {
    return 99999;
}

uint32_t getpid() {
    return 40;
}

FILE open(char* path, uint32_t offset) {
    return kernel_fopen(path, offset);
}

uint32_t read(FILE fid, char* buffer, size_t length) {
    return kernel_fread(fid, length, buffer);
}

uint32_t write(FILE fid, char* buffer, size_t length) {
    for(uint32_t i = 0; i < length; i++) {
        TerminalPrintCharacter(buffer[i]);
    }
    return kernel_fwrite(fid, length, buffer);
}

void SetupSyscalls() {
    ISRInstallHandler(ISR_SYSCALL, SyscallHandler);
}

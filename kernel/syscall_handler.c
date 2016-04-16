#include <stdio.h>
#include <stdint.h>

#include <arch/interrupts.h>
#include <arch/registers.h>

#include <devices/ps2keyboard.h>

#include <panic.h>
#include <syscall_handler.h>
#include <terminal.h>

void SyscallHandler(registers_t* registers) {
    switch(registers->EAX) {
        case SYSCALL_EXIT:
            registers->EAX = syscall_exit(registers);
        case SYSCALL_FORK:
            registers->EAX = syscall_fork(registers);
            return;
        case SYSCALL_OPEN:
            registers->EAX = open((char*) registers->EBX, registers->ECX);
            return;
        case SYSCALL_CLOSE:
            return;
        case SYSCALL_READ:
            registers->EAX = read(registers->EBX, (char*) registers->ECX, (size_t) registers->EDX);
            return;
        case SYSCALL_WRITE:
            registers->EAX = write(registers->EBX, (char*) registers->ECX, (size_t) registers->EDX);
            return;
        case SYSCALL_MALLOC:
        case SYSCALL_FREE:
        case SYSCALL_GETSTDIN:
        case SYSCALL_GETSTDOUT:
        case SYSCALL_GETSTDERR:
        case SYSCALL_LSEEK:
        case SYSCALL_GETPID:
        case SYSCALL_MOUNT:
        case SYSCALL_UMOUNT:
        case SYSCALL_REBOOT:
        case SYSCALL_SYNC:
            return;
        default:
            KernelPanic("Tried to make an invalid syscall.", registers);
            return;
    }
    return;
}

uint32_t syscall_exit(registers_t* registers) {
    return registers->EAX;
}

uint32_t syscall_fork(registers_t* registers) {
    return 0;
}

uint32_t syscall_getpid() {
    return 0;
}

FILE open(char* path, uint32_t offset) {
    return 0;
}

uint32_t read(FILE fid, char* buffer, size_t length) {
    return 0;
}

uint32_t write(FILE fid, char* buffer, size_t length) {
    // TODO: This is an ugly hack. Actually write to stdout.
    for(uint32_t i = 0; i < length; i++) {
        TerminalPrintCharacter(buffer[i]);
    }
    return 0;
}

void SetupSyscalls() {
    ISRInstallHandler(ISR_SYSCALL, SyscallHandler);
}

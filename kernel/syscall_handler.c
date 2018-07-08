/**
 * syscall_handler.c
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

#include <stdio.h>
#include <stdint.h>

#include <arch/interrupts.h>
#include <arch/registers.h>

#include <devices/ps2keyboard.h>

#include <devices/video/lfb_terminal.h>
#include <devices/video/vga.h>

#include <memory/liballoc.h>

#include <panic.h>
#include <syscall_handler.h>
#include <terminal.h>

void SyscallHandler(registers_t* registers) {
    switch(registers->EAX) {
        case SYSCALL_EXIT:
            registers->EAX = syscall_exit(registers);
            return;
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
            registers->EAX = malloc((size_t) registers->EBX);
            //registers->EAX = ManagerAllocate((size_t) registers->EBX);
            return;
        case SYSCALL_FREE:
            free((uintptr_t) registers->EBX);
            //registers->EAX = ManagerFree((uintptr_t) registers->EBX);
            return;
        case SYSCALL_GETSTDIN:
            return;
        case SYSCALL_GETSTDOUT:
            return;
        case SYSCALL_GETSTDERR:
            return;
        case SYSCALL_LSEEK:
            return;
        case SYSCALL_GETPID:
            return;
        case SYSCALL_MOUNT:
            return;
        case SYSCALL_UMOUNT:
            return;
        case SYSCALL_REBOOT:
            return;
        case SYSCALL_SYNC:
            return;
        default:
            KernelPanic("Tried to make an invalid syscall.", registers);
            return;
    }
    return;
}

uint32_t syscall_exit(registers_t* registers) {
    // TODO: Actually end the process.
    return registers->EAX;
}

uint32_t syscall_fork(registers_t* registers) {
    // TODO: Actually fork the process.
    printf("Attempted to fork a process.\n");
    return 0;
}

uint32_t syscall_getpid() {
    // TODO: Implement PIDs.
    return 0;
}

FILE open(char* path, uint32_t offset) {
    return 0;
}

uint32_t read(FILE fid, char* buffer, size_t length) {
    return 0;
}

uint32_t write(FILE fid, char* buffer, size_t length) {
    /* TODO: Ugly hack with intercepting syscalls for printf. Eventually allow
     * writing to a "stdout" and then support real files. */

    if(LFBTerminalIsEnabled()) {
        for(size_t i = 0; i < length; i++) {
            LFBTerminalPrintCharacter(buffer[i]);
        }
    } else {
        for(size_t i = 0; i < length; i++) {
            TerminalPrintCharacter(buffer[i]);
        }
    }

    return 0;
}

void SetupSyscalls() {
    ISRInstallHandler(ISR_SYSCALL, SyscallHandler);
}

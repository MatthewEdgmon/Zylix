/**
 * syscall.c - x86_64 syscall handler.
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

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "isr.h"
#include "syscall.h"

#include <arch/interrupts.h>
#include <arch/registers.h>
#include <arch/syscalls.h>

#include <devices/video/lfb_terminal.h>
#include <devices/video/vga.h>
#include <devices/ps2keyboard.h>

#include <memory/liballoc.h>

#include <panic.h>
#include <terminal.h>

void SyscallHandler(cpu_registers_t* registers) {
    switch(registers->rax) {
        case SYSCALL_EXIT:
            registers->rax = syscall_exit(registers);
            return;
        case SYSCALL_FORK:
            registers->rax = syscall_fork(registers);
            return;
        case SYSCALL_OPEN:
            registers->rax = open((char*) registers->rbx, registers->rcx);
            return;
        case SYSCALL_CLOSE:
            return;
        case SYSCALL_READ:
            registers->rax = read(registers->rbx, (char*) registers->rcx, (size_t) registers->rdx);
            return;
        case SYSCALL_WRITE:
            registers->rax = write(registers->rbx, (char*) registers->rcx, (size_t) registers->rdx);
            return;
        case SYSCALL_MALLOC:
            registers->rax = malloc((size_t) registers->rbx);
            //registers->rax = ManagerAllocate((size_t) registers->rbx);
            return;
        case SYSCALL_FREE:
            free((uintptr_t) registers->rbx);
            //registers->rax = ManagerFree((uintptr_t) registers->rbx);
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

uint32_t syscall_exit(cpu_registers_t* registers) {
    // TODO: Actually end the process.
    return registers->rax;
}

uint32_t syscall_fork(cpu_registers_t* registers) {
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

    /* TODO: Even uglier hack! We're putting all writes to RS232 here. */
    // WriteRS232(stuff)

    return 0;
}

void SetupSyscalls() {
    ISRInstallHandler(ISR_SYSCALL, SyscallHandler);
}

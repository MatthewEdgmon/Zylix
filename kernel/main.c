#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include <arch/io.h>
#include <arch/interrupts.h>
#include <arch/cpu.h>
#include <arch/cpu_info.h>

#include <devices/acpi.h>
#include <devices/cmos.h>
#include <devices/ps2.h>
#include <devices/ps2keyboard.h>
#include <devices/ps2mouse.h>
#include <devices/pci.h>
#include <devices/smbios.h>

#include <filesystem/vfs.h>
#include <filesystem/stdout.h>
#include <filesystem/stderr.h>
#include <filesystem/stdin.h>
#include <filesystem/null.h>

#include <menu/shell.h>

#include <common.h>
#include <execute.h>
#include <lock.h>
#include <logo.h>
#include <logging.h>
#include <multiboot.h>
#include <panic.h>
#include <scheduler.h>
#include <syscall_handler.h>
#include <terminal.h>
#include <vga.h>

uintptr_t initial_esp;

int main(multiboot_info_t* multiboot_info, uint32_t multiboot_magic, uintptr_t esp) {

    initial_esp = esp;

    SetupTerminal();
    TerminalSetColor(TerminalMakeColor(COLOR_WHITE, COLOR_BLACK));

    SetupCPU();
    SetupSyscalls();
    SetupLocks();
    SetupScheduler();

    if(multiboot_magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        printf("Didn't receive right multiboot magic: 0x%X\n", multiboot_magic);
        return 1;
    }

    MultibootDumpInfo(multiboot_info);

    printf("CPU Information:\n");
    printf("    Arch: %s\n", GetCPUArchitecture());
    printf("    Vendor: %s\n", GetCPUVendor());
    printf("    Brand: %s\n", GetCPUBrand());
    printf("    Features: %s\n", GetCPUFeatures());
    printf("    Max Request: 0x%X\n", GetCPUMaxRequestLevel());

    printf("Setting up SMBIOs.\n");
    SetupSMBIOS();

    printf("Setting up PS/2 controller and devices.\n");
    SetupA20();
    SetupPS2();
    SetupPS2Keyboard();
    //SetupPS2Mouse();

    printf("Switching to ACPI mode.\n");
    SetupACPI();

    printf("Setting up CMOS chip.\n");
    SetupRTC();
    CMOSReadRTC();
    printf("Current date and time: %d/%d/%d %d:%d:%d \n", CMOSGetMonth(), CMOSGetDay(), CMOSGetYear(),
                                                          CMOSGetHours(), CMOSGetMinutes(), CMOSGetSeconds());

    SetupShell();

    int exit_status = 0;

    while(!exit_status) {

    }

    return 0;
}

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

#include <error.h>
#include <execute.h>
#include <lock.h>
#include <logo.h>
#include <logging.h>
#include <vga.h>
#include <terminal.h>
#include <process.h>
#include <syscall_handler.h>
#include <multiboot.h>

#include <menu/menu.h>

uintptr_t initial_esp;

int main(struct multiboot* multiboot_header, uint32_t multiboot_magic, uintptr_t esp) {

    initial_esp = esp;

    SetupTerminal();

    SetupCPU();

    SetupSyscalls();

    PrintLogo();

    if(multiboot_magic != MULTIBOOT_EAX_MAGIC) {
        printf("Didn't receive right multiboot magic! 0x%X\n", multiboot_magic);
    } else {
        printf("Got multiboot magic number: 0x%X\n", multiboot_magic);
    }

    printf("CPU Information:\n");
    printf("    Arch: %s \n", GetCPUArchitecture());
    printf("    Vendor: %s \n", GetCPUVendor());
    printf("    Brand: %s \n", GetCPUBrand());
    printf("    Features: %s \n", GetCPUFeatures());
    printf("    Max Request: 0x%X \n", GetCPUMaxRequestLevel());

    printf("Setting up SMBIOS.\n");
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

    printf("Enabling multiprocessing.\n");
    SetupMultiProcess();

    int exit_status = 0;

    while(!exit_status) {

    }

    return 0;
}

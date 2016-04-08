/*  ______       _  _
   |___  /      | |(_)
      / / _   _ | | _ __  __
     / / | | | || || |\ \/ /
    / /__| |_| || || | >  <
   /_____|\__, ||_||_|/_/\_\
           __/ |
          |___/              */

#include <libc/stddef.h>
#include <libc/stdint.h>
#include <libc/stdio.h>
#include <libc.h>

#include <arch/io.h>
#include <arch/interrupts.h>
#include <arch/cpu.h>
#include <arch/cpu_info.h>

#include <common.h>
#include <devices/cmos.h>
#include <devices/ps2.h>
#include <devices/ps2keyboard.h>
#include <devices/ps2mouse.h>
#include <devices/pci.h>
#include <devices/smbios.h>
#include <devices/speaker.h>
#include <error.h>
#include <execute.h>
#include <lock.h>
#include <shell.h>
#include <vga.h>
#include <terminal.h>

#include <menu/monitor.h>

void PrintLogo() {
    TerminalSetColor(TerminalMakeColor(COLOR_LIGHT_GREEN, COLOR_BLACK));
    printf("  ______       _  _       \n");
    printf(" |___  /      | |(_)      \n");
    printf("    / / _   _ | | _ __  __\n");
    printf("   / / | | | || || |\\ \\/ /\n");
    printf("  / /__| |_| || || | >  < \n");
    printf(" /_____|\\__, ||_||_|/_/\\_\\\n");
    printf("         __/ |            \n");
    printf("        |___/             \n");
    TerminalSetColor(TerminalMakeColor(COLOR_WHITE, COLOR_BLACK));
}

int KernelMain() {

    SetupTerminal();

    SetupCPU();

    PrintLogo();

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

    //printf("Setting up kernel debug shell.\n");
    //SetupShell();

    //printf("Launching RAM monitor.\n");
    //RAMMonitorMain();

    int exit_status = 0;

    while(!exit_status) {
        //Shell();
        //printf(getc());
    }

    return 0;

}

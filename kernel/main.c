/*  ______       _  _       
   |___  /      | |(_)      
      / / _   _ | | _ __  __
     / / | | | || || |\ \/ /
    / /__| |_| || || | >  < 
   /_____|\__, ||_||_|/_/\_\
           __/ |            
          |___/              */

#include <stddef.h>
#include <stdint.h>
#include <libc.h>

#include <arch/IO.h>
#include <arch/CPUInfo.h>
#include <arch/SetupCPU.h>

#include <common.h>
#include <devices/ps2.h>
#include <devices/ps2keyboard.h>
#include <devices/ps2mouse.h>
#include <devices/pci.h>
#include <devices/speaker.h>
#include <error.h>
#include <execute.h>
#include <shell.h>
#include <vga.h>
#include <terminal.h>

void PrintLogo() {
    TerminalSetColor(TerminalMakeColor(COLOR_LIGHT_GREEN, COLOR_BLACK));
    TerminalPrintString("  ______       _  _       \n");
    TerminalPrintString(" |___  /      | |(_)      \n");
    TerminalPrintString("    / / _   _ | | _ __  __\n");
    TerminalPrintString("   / / | | | || || |\\ \\/ /\n");
    TerminalPrintString("  / /__| |_| || || | >  < \n");
    TerminalPrintString(" /_____|\\__, ||_||_|/_/\\_\\\n");
    TerminalPrintString("         __/ |            \n");
    TerminalPrintString("        |___/             \n");
    TerminalSetColor(TerminalMakeColor(COLOR_WHITE, COLOR_BLACK));
}

int KernelMain() {

    SetupCPU();

    SetupTerminal();

    PrintLogo();

    TerminalPrintString("Zylix Version 0.0.1 Starting.\n");

    TerminalPrintString("CPU Information:\n");
    TerminalPrintString("    Vendor:\n");
    TerminalPrintString("    Brand:\n");
    TerminalPrintString("    Features:\n");

    TerminalPrintString("Setting up PS/2 controller and devices.\n");
    SetupPS2();
    PS2EnableA20();

    TerminalPrintString("Setting up kernel debug shell.\n");
    SetupShell();

    // TODO: libc
    // TODO: x86 arch code

    int exit_status = 0;

    while(!exit_status) {
        //Shell();
    }

    return 0;

}
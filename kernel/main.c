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

#include <arch/IO.h>
#include <arch/CPUInfo.h>
#include <arch/SetupCPU.h>

#include <common.h>
#include <devices/ps2.h>
#include <devices/ps2keyboard.h>
#include <devices/ps2mouse.h>
#include <devices/pci.h>
#include <devices/speaker.h>
#include <elf_loader.h>
#include <error.h>
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

    TerminalPrintString(">\n");

    uint8_t loop = 0x01;

    while(loop) {

    }

    return 0;

}
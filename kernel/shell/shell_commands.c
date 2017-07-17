#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include <arch/cpu_info.h>
#include <arch/io.h>

#include <devices/video/bga.h>
#include <devices/video/lfb_terminal.h>
#include <devices/video/vesa.h>
#include <devices/video/vga.h>
#include <devices/cmos.h>

#include <shell/shell_commands.h>
#include <shell/shell.h>

#include <panic.h>
#include <terminal.h>
#include <multiboot.h>

void CommandEcho() {

}

void CommandClear() {
    if(LFBTerminalIsEnabled()) {
        LFBTerminalClear();
    } else {
        TerminalClear();
    }
}

void CommandLogo() {
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

void CommandClock() {
    printf("%d/%d/%04d %d:%02d:%02d\n", CMOSGetMonth(), CMOSGetDay(), CMOSGetYear(),
                                        CMOSGetHours(), CMOSGetMinutes(), CMOSGetSeconds());
}

void CommandCPUInfo() {
    DumpCPUInformation();
}

void CommandSMBIOSInfo() {
    SMBIOSDumpInfo();
}

void CommandPanic() {
    KernelPanic("Testing kernel panic.", NULL);
}

void CommandExplode() {
    uint16_t* video_memory = (uint16_t*) 0xB8000;

    uint16_t fun_index = 0;
    int random1 = 0;
    int random2 = 10;

    while(1) {
        video_memory[fun_index] = random1;
        random1 = random2 + random2;
        random1--;
        random2--;
        fun_index = fun_index + random1;
        if(random1 == 0 || random2 == 0) {
            random1 = 32323 + fun_index;
            random2 = 11 - fun_index;
        }
        if(fun_index >= 25 * 80) {
            fun_index = fun_index - random2;
        }
    }
}

void CommandShutdown() {
    for(const char *s = "Shutdown"; *s; ++s) {
        outb(0x8900, *s);
    }
    outb(0xF4, 0x00);
}

void CommandBGAStart() {
    SetupBGA();
}

void CommandVGADump() {
    VGADumpRegisters();
}

void CommandVGAText40x25() {
    VGASetTextMode(40, 25);
}

void CommandVGAText40x50() {
    VGASetTextMode(40, 50);
}

void CommandVGAText80x25() {
    VGASetTextMode(80, 25);
}

void CommandVGAText80x50() {
    VGASetTextMode(80, 50);
}

void CommandVGAText90x30() {
    VGASetTextMode(90, 30);
}

void CommandVGAText90x60() {
    VGASetTextMode(90, 60);
}

void CommandVGAGraphics640x480x16() {
    VGASetGraphicsMode(640, 480, 16);
}

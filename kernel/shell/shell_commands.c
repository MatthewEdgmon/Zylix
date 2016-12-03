#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include <devices/cmos.h>
#include <devices/vesa.h>
#include <devices/vga.h>

#include <shell/shell_commands.h>
#include <shell/shell.h>

#include <logo.h>
#include <panic.h>
#include <terminal.h>
#include <multiboot.h>

void CommandEcho() {

}

void CommandClear() {
    TerminalClear();
}

void CommandLogo() {
    PrintLogo();
}

void CommandClock() {
    CMOSReadRTC();
    printf("Current date and time: %d/%d/%d %d:%d:%d \n", CMOSGetMonth(), CMOSGetDay(), CMOSGetYear(),
                                                          CMOSGetHours(), CMOSGetMinutes(), CMOSGetSeconds());
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

void CommandStartVideo() {
    SetupVGA();
}

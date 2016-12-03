#include <stdint.h>
#include <stdbool.h>

#include <devices/cmos.h>

#include <menu/shell.h>
#include <menu/shell_commands.h>
#include <menu/monitor.h>

#include <panic.h>
#include <terminal.h>

void CommandEcho() {

}

void CommandClear() {
    TerminalClear();
}

void CommandPing() {
    printf("Pong!\n");
}

void CommandLogo() {
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

void CommandLaunchCode() {
    TerminalSetColor(TerminalMakeColor(COLOR_LIGHT_BLUE, COLOR_WHITE));
    TerminalPrintString("                  .oo.                  \n");
    TerminalPrintString("                `+s--s+`                \n");
    TerminalPrintString("               .y/    \\y.               \n");
    TerminalPrintString("              .h:      :h.              \n");
    TerminalPrintString("              so  \\--/  os              \n");
    TerminalPrintString("           :h-`h:      :h`-h:           \n");
    TerminalPrintString("           .h. /h`    `h\\ .h.           \n");
    TerminalPrintString("            os`oho####oho`so            \n");
    TerminalPrintString("            .hy+-h:yy:h-+yh.            \n");
    TerminalPrintString("             --  +s--s+  --             \n");
    TerminalPrintString("                 `y::y`                 \n");
    TerminalPrintString("                  \\hh/                  \n");
    TerminalPrintString("                   ++                   \n");
    TerminalPrintString("                                        \n");
    TerminalPrintString("                                        \n");
    TerminalPrintString("            +sssssssssssss+             \n");
    TerminalPrintString("                                        \n");
    TerminalSetColor(TerminalMakeColor(COLOR_WHITE, COLOR_BLACK));
}

void CommandClock() {
    CMOSReadRTC();
    printf("Current date and time: %d/%d/%d %d:%d:%d \n", CMOSGetMonth(), CMOSGetDay(), CMOSGetYear(),
                                                          CMOSGetHours(), CMOSGetMinutes(), CMOSGetSeconds());
}

void CommandMonitor() {
    RAMMonitorMain();
}

void CommandPanic() {
    KernelPanic("User panic.", NULL);
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

void CommandBrowser() {
    BrowserMain();
}

void CommandFizzBuzz() {
    for(int i = 1; i <= 100; i++) {
        if(i % 3 == 0 && i % 5 == 0) {
            printf("FizzBuzz ");
        } else if(i % 3 == 0) {
            printf("Fizz ");
        } else if(i % 5 == 0) {
            printf("Buzz ");
        } else {
            printf("%d ", i);
        }

        /* Every 10 numbers make a newline. */
        if(i % 10 == 0) {
            printf("\n");
        }
    }
}

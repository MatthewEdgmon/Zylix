#include <stdio.h>

#include <logo.h>

#include <terminal.h>

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

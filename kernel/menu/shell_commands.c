#include <menu/shell.h>
#include <menu/shell_commands.h>

#include <terminal.h>

void CommandEcho() {

}

void CommandClear() {
    TerminalClear();
}

void CommandPing() {
    TerminalPrintString("Pong!");
}

void CommandLogo() {
    TerminalPrintString("\n");
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

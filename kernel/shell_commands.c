#include <shell.h>
#include <shell_commands.h>

#include <terminal.h>

void CommandHelp() {

}

void CommandClear() {
    TerminalClear();
}

void CommandPing() {
    TerminalPrintString("Pong!");
}
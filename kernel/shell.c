/**
 * A kernel shell. This is not a userspace shell, all commands are run in kernel mode.
 */
#include <shell.h>
#include <shell_commands.h>
#include <types.h>
#include <terminal.h>
#include <libc.h>

int number_of_commands = 0;

command_table_t command_table[MAX_COMMANDS];

void AddShellCommand(char* name, char* description, void* function) {
    if(number_of_commands + 1 < MAX_COMMANDS) {
        number_of_commands++;
        command_table[number_of_commands].name = name;
        command_table[number_of_commands].description = description;
        command_table[number_of_commands].function = function;
    }
}

void FindShellCommand(char* name) {
    for(int i = 0; i < number_of_commands + 1; i++) {

    }
}

void Shell() {

    TerminalPrintString("\n>");

}

void SetupShell() {
    AddShellCommand("help", "Lists available commands.", CommandHelp);
}
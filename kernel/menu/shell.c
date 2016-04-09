/**
 * A kernel shell. This is not a userspace shell, all commands are run in kernel mode.
 */
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <menu/shell.h>
#include <menu/shell_commands.h>

#include <terminal.h>

typedef void (*shell_command_pointer_t)();

/* Table of commands. */
command_table_t command_table[MAX_COMMANDS];

/* Array of previous commands for history. */
char* previous_commands[MAX_HISTORY];
char* input_string = "ping";

int number_of_commands = 0;

void CommandEmpty() {
    /* Do nothing. */
    return;
}

/* Iterate through the table and print the name and description. */
void CommandHelp() {
    for(int i = 2; i <= number_of_commands; i++) {
        TerminalPrintString("\n");
        TerminalPrintString(command_table[i].name);
        TerminalPrintString(" - ");
        TerminalPrintString(command_table[i].description);
    }
}

void AddShellCommand(char* name, char* description, shell_command_pointer_t function) {
    if(number_of_commands + 1 < MAX_COMMANDS) {
        number_of_commands++;
        command_table[number_of_commands].name = name;
        command_table[number_of_commands].description = description;
        command_table[number_of_commands].function = function;
    }
}

int FindShellCommand(char* name) {
    int comparison = 0;
    for(int i = 0; i < number_of_commands + 1; i++) {
        comparison = strcmp(name, command_table[i].name);

        if(comparison == 0) {
            return i;
        } else {
            return -1;
        }
    }
    return -1;
}

void Shell() {

    printf("\n>");
    gets(input_string);

    void (*command_function)(void);

    int i = FindShellCommand(input_string);

    /* If we match the input to a command, execute it, else do nothing. */
    if(i >= 0) {
        command_function = command_table[i].function;
        command_function();
    } else {
        return;
    }

    return;
}

void SetupShell() {
    AddShellCommand("", "", CommandEmpty);
    AddShellCommand("help", "Lists available commands.", CommandHelp);
    AddShellCommand("echo", "Prints what comes after the command.", CommandEcho);
    AddShellCommand("clear", "Clears the screen.", CommandClear);
    AddShellCommand("ping", "Pong!.", CommandClear);
    AddShellCommand("logo", "Prints the Zylix logo.", CommandClear);
}

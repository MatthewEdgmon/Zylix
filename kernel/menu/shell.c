/**
 * A kernel shell. This is not a userspace shell, all commands are run in kernel mode.
 */
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <menu/shell.h>
#include <menu/shell_commands.h>

#include <terminal.h>

#define MAX_COMMANDS 100

typedef void (*func_pointer_t)();

typedef struct {
    char* name;
    char* description;
    func_pointer_t function;
} command_table_t;

/* Table of commands. */
command_table_t command_table[MAX_COMMANDS];

int number_of_commands = 0;

void CommandEmpty() {
    /* Do nothing. */
    return;
}

/* Iterate through the table and print the name and description. */
void CommandHelp() {
    for(int i = 2; i <= number_of_commands; i++) {
        printf("%s - %s\n", command_table[i].name, command_table[i].description);
    }
}

void AddShellCommand(char* name, char* description, func_pointer_t function) {
    if(number_of_commands + 1 < MAX_COMMANDS) {
        number_of_commands++;
        command_table[number_of_commands].name = name;
        command_table[number_of_commands].description = description;
        command_table[number_of_commands].function = function;
    }
}

int FindShellCommand(char* name) {
    int comparison = 0;
    for(int i = 2; i < number_of_commands + 1; i++) {
        comparison = strcmp(name, command_table[i].name);
        if(comparison == 0) {
            return i;
        }
    }
    return -1;
}

void Shell(char* input) {

    func_pointer_t command_function;

    int i = FindShellCommand(input);

    /* If we match the input to a command, execute it, else do nothing. */
    if(i != -1) {
        command_function = command_table[i].function;
        command_function();
    } else {
        printf("No valid command.\n");
    }

    printf(">");
}

void SetupShell() {
    AddShellCommand("", "", CommandEmpty);
    AddShellCommand("help", "Lists available commands.", CommandHelp);
    AddShellCommand("echo", "Prints what comes after the command.", CommandEcho);
    AddShellCommand("clear", "Clears the screen.", CommandClear);
    AddShellCommand("ping", "Pong!", CommandPing);
    AddShellCommand("logo", "Prints the Zylix logo.", CommandLogo);
    AddShellCommand("launchcode", "Prints the LaunchCode logo.", CommandLaunchCode);
    AddShellCommand("clock", "Prints the date and time.", CommandClock);
    AddShellCommand("monitor", "Starts the RAM monitor.", CommandMonitor);
    AddShellCommand("panic", "Test kernel panic.", CommandPanic);
    AddShellCommand("explode", "Fun!", CommandExplode);
    AddShellCommand("browser", "File browser.", CommandBrowser);
    printf(">");
}

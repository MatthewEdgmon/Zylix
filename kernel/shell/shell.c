/**
 * shell.c - Built-in kernel shell.
 *
 * This file is part of Zylix.
 *
 * Zylix is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Zylix is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Zylix.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <shell/shell.h>
#include <shell/shell_commands.h>

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
    AddShellCommand("cpu_info", "Dumps information about your CPU.", CommandCPUInfo);
    AddShellCommand("smbios_info", "Dumps information about the SMBIOS.", CommandSMBIOSInfo);
    AddShellCommand("logo", "Prints the Zylix logo.", CommandLogo);
    AddShellCommand("clock", "Prints the date and time.", CommandClock);
    AddShellCommand("panic", "Test kernel panic.", CommandPanic);
    AddShellCommand("explode", "Fun!", CommandExplode);
    AddShellCommand("shutdown", "Shuts down the computer (emulator only).", CommandShutdown);
    AddShellCommand("ata_setup_pio", "Setup the ATA PIO mode driver.", CommandATASetupPIO);
    AddShellCommand("ata_reset_pio", "Reset the ATA PIO mode driver.", CommandATAResetPIO);
    AddShellCommand("ata_test_pio", "Perform a test read using the ATA PIO mode driver.", CommandATATestPIO);
    AddShellCommand("ata_setup_dma", "Setup the ATA DMA mode driver.", CommandATASetupDMA);
    AddShellCommand("ata_reset_dma", "Reset the ATA DMA mode driver.", CommandATAResetDMA);
    AddShellCommand("ata_test_dma", "Perform a test read using the ATA DMA mode driver.", CommandATATestDMA);
    AddShellCommand("bga_start", "Attempts to start Bochs Graphics Adapter.", CommandBGAStart);
    AddShellCommand("vga_dump", "Dumps the state of the VGA registers.", CommandVGADump);
    AddShellCommand("vga_40_25", "Starts VESA/VGA 40x25 text mode.", CommandVGAText40x25);
    AddShellCommand("vga_40_50", "Starts VESA/VGA 40x50 text mode.", CommandVGAText40x50);
    AddShellCommand("vga_80_25", "Starts VESA/VGA 80x25 text mode.", CommandVGAText80x25);
    AddShellCommand("vga_80_50", "Starts VESA/VGA 80x50 text mode.", CommandVGAText80x50);
    AddShellCommand("vga_90_30", "Starts VESA/VGA 90x30 text mode.", CommandVGAText90x30);
    AddShellCommand("vga_90_60", "Starts VESA/VGA 90x60 text mode.", CommandVGAText90x60);
    AddShellCommand("vga_640_480", "Starts VESA/VGA 640x480x16 graphics mode.", CommandVGAGraphics640x480x16);
    printf(">");
}

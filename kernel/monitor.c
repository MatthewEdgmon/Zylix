/**
 * First real program for the OS, a RAM monitor!
 */

#include <libc/stddef.h>
#include <libc/stdio.h>
#include <libc/stdint.h>
#include <libc/string.h>

#include <devices/ps2.h>
#include <devices/ps2keyboard.h>

#include <monitor.h>
#include <terminal.h>
#include <vga.h>

/* I am a horrible person. */
void RAMMonitorSeizure() {

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

/**
 * No "main" here, built as a part of the kernel
 */
int RAMMonitorMain() {

    //uint16_t* current_address = (uint16_t*) 0xB8000;
    uint16_t* current_address = (uint16_t*) 0xB8000;

    uint16_t* selected_address = (uint16_t*) 0xB8000;
    uint16_t selected_value = 0;

    uint8_t response = 0;

    /* Main loop. */
    while(1) {

        current_address = selected_address - 12;

        /* Display the lines above the selected address. */
        for(int i = 0; i < 11; i++) {
            current_address++;
            /* Print the address in blue. */
            TerminalSetColor(TerminalMakeColor(COLOR_LIGHT_BLUE, COLOR_BLACK));
            printf("0x%X: ", current_address);
            /* Print the data in white. */
            TerminalSetColor(TerminalMakeColor(COLOR_WHITE, COLOR_BLACK));
            printf("0x%X ", current_address);
            /* And finally a newline. */
            printf("\n");
        }

        /* Display the selected address. */
        current_address++;
        /* Print the address in red. */
        TerminalSetColor(TerminalMakeColor(COLOR_LIGHT_RED, COLOR_BLACK));
        printf("0x%X: ", current_address);
        /* Print the data in white. */
        TerminalSetColor(TerminalMakeColor(COLOR_WHITE, COLOR_BLACK));
        printf("0x%X ", current_address);
        /* And finally a newline. */
        printf("\n");

        /* Display the lines below the selected address. */
        for(int i = 0; i < 11; i++) {
            current_address++;
            /* Print the address in blue. */
            TerminalSetColor(TerminalMakeColor(COLOR_LIGHT_BLUE, COLOR_BLACK));
            printf("0x%X: ", current_address);
            /* Print the data in white. */
            TerminalSetColor(TerminalMakeColor(COLOR_WHITE, COLOR_BLACK));
            printf("0x%X ", current_address);
            /* And finally a newline. */
            printf("\n");
        }

        /* The second to last line displays key commands. */
        printf("(S)et Value (Down)\\(Up) Change Address. (<)\\(>) Change Value. (Shift) x10\n");

        /* The bottom line displays selected values. */
        TerminalSetColor(TerminalMakeColor(COLOR_WHITE, COLOR_BLACK));
        printf("Selected Address:");
        TerminalSetColor(TerminalMakeColor(COLOR_LIGHT_RED, COLOR_BLACK));
        printf(" 0x%X ", selected_address);
        TerminalSetColor(TerminalMakeColor(COLOR_WHITE, COLOR_BLACK));
        printf("Selected Value:");
        TerminalSetColor(TerminalMakeColor(COLOR_LIGHT_GREEN, COLOR_BLACK));
        printf(" 0x%X ", selected_value);
        TerminalSetColor(TerminalMakeColor(COLOR_WHITE, COLOR_BLACK));

        /* Handle input. */
        while(1) {

            // TODO: REPLACE WITH ACTUAL STD LIB INPUT FUNCTIONS.
            printf("%c\r", PS2KeyboardGetKey());

            /* Check if shift is held. */
            /* Check changing address. */
            /* Check changing value. */
            /* Check setting value. */
        }

    }

    return 0;
}

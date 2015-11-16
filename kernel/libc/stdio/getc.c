#include <libc/stdio.h>

#include <devices/ps2.h>
#include <devices/ps2keyboard.h>

char getc() {
    char current_key = PS2KeyboardGetKey();
    char current_extended_key = PS2KeyboardGetExtendedKey();

    /* Are we dealing with an extended key? */
    if(current_key == 0xFF) {
        /* Yes. */
        return current_extended_key;
    } else {
        /* No. */
        return current_key;
    }
    return 0;
}
#include <arch/IO.h>

#include <devices/ps2.h>
#include <devices/ps2keyboard.h>

void KeyboardSelfTest() {
    uint8_t response;

    outb(0x64, 0xFF);
    io_wait();
    response = inb(0x60);

    switch(response) {
        case 0xAA:
            TerminalPrintString("Self-test passed.");
            break;
        case 0xFA:
            TerminalPrintString("Unexpected ACK.");
            break;
        case 0xFC:
            TerminalPrintString("Self-test failed.");
            break;
        case 0xFD:
            TerminalPrintString("Self-test failed.");
            break;
        case 0xFE:
            TerminalPrintString("Resend requested.");
            break;
        default:
            TerminalPrintString("Got unknown Keyboard response.");
            break;
    }

}

void KeyboardEnableScanning() {
    uint8_t response;
    outb(0x64, 0xF5);
    io_wait();
    response = inb(0x60);

    if(response == 0xFA) {
        TerminalPrintString("KeyboardEnableScanning() got an ACK");
    }

    if(response == 0xFE) {
        TerminalPrintString("KeyboardEnableScanning() got a resend request.");
    }

}

void KeyboardDisableScanning() {
    uint8_t response;
    outb(0x64, 0xF5);
    io_wait();
    response = inb(0x60);

    if(response == 0xFA) {
        TerminalPrintString("keyboard_disable_scanning() got an ACK");
    }

    if(response == 0xFE) {
        TerminalPrintString("keyboard_disable_scanning() got a resend request.");
    }

}

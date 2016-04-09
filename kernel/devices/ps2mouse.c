#include <stdint.h>

#include <devices/ps2.h>
#include <devices/ps2mouse.h>

#include <common.h>
#include <terminal.h>

void PS2MouseDisableDataReporting() {
    uint8_t response;

    /* Tell the PS/2 controller we're writing to port 2. */
    PS2WaitInputBuffer();
    PS2SendCommand(PS2_COMMAND_WRITE_PORT2_INPUT);

    PS2SendCommand(0xFF);
    response = PS2ReadData();

    if(response == 0xFA) {
        TerminalPrintString("PS2 Mouse data reporting disabled.");
    }
}

void PS2MouseEnableDataReporting() {
    uint8_t response;
    PS2SendCommand(0xFF);
    response = PS2ReadData();

    if(response == 0xFA) {
        TerminalPrintString("PS2 Mouse data reporting enabled.");
    }
}

void PS2MouseGetDataPacket() {
    uint8_t byte1 = 0x00;
    uint8_t byte2 = 0x00;
    uint8_t byte3 = 0x00;

    PS2WaitOutputBuffer();
    byte1 = PS2ReadData();
    PS2WaitOutputBuffer();
    byte2 = PS2ReadData();
    PS2WaitOutputBuffer();
    byte3 = PS2ReadData();

    if(BIT_CHECK(byte1, 3) == 0) {
        TerminalPrintString("PS2 Mouse sent errant packet data.");
    }
}

/**
 * Asks the mouse to send us a packet
 */
void PS2MouseCheckConnection() {

    /*

    PS2SendCommand(PS2_MOUSE_)

    */

    // Send 0xEB
    // If receive 0xFA AND blank mouse packet
    // Then mouse is still connected, return
    // Else wait mouse is disconnected

}

void SetupPS2Mouse() {
    uint8_t response_byte;

    /* Tell the PS/2 controller we're writing to port 2. */
    PS2WaitInputBuffer();
    PS2SendCommand(PS2_COMMAND_WRITE_PORT2_INPUT);

    PS2WaitInputBuffer();
    PS2SendCommand(PS2_MOUSE_SET_DEFAULTS);
}

/* Handler for IRQ12 */
void PS2MouseHandler() {

}

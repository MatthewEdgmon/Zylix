
#include <devices/ps2.h>
#include <devices/ps2mouse.h>

#include <common.h>
#include <types.h>
#include <terminal.h>

void PS2MouseReset() {
    uint8_t response;
    PS2SendCommand(0xFF);
    response = PS2ReadData();

    if(response == 0xFA) {
        TerminalPrintString("PS2 Mouse reset.");
    }

}

void PS2MouseResend() {
    uint8_t response;
    PS2SendCommand(0xFF);
    response = PS2ReadData();

    if(response == 0xFA) {
        TerminalPrintString("PS2 Mouse reset.");
    }

}

void PS2MouseDisableDataReporting() {
    uint8_t response;
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
    uint8_t byte1;
    uint8_t byte2;
    uint8_t byte3;

    byte1 = PS2ReadData();
    byte2 = PS2ReadData();
    byte3 = PS2ReadData();

    if(BIT_CHECK(byte1, 3) == 0) {
        TerminalPrintString("PS2 Mouse send errant packet data.");
    }
}
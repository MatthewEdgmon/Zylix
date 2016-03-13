#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include <libc/stdint.h>

/* Ports associated with the PS/2 Controller. */
#define PS2_DATA_PORT                  0x60
#define PS2_STATUS_REGISTER            0x64
#define PS2_COMMAND_REGISTER           0x64

/* PS/2 controller commands. */
#define PS2_COMMAND_READ_BYTE_ZERO     0x20    /* Reads byte 0 from internal ram, also the Controller Configuration Byte. */
#define PS2_COMMAND_READ_BYTE_N        0x21    /* Where 'N' is the command byte & 0x1F. */
#define PS2_COMMAND_WRITE_BYTE_ZERO    0x60    /* Write next byte to "byte 0" of internal RAM, or the Controller Configuration Byte. */
#define PS2_COMMAND_WRITE_BYTE_N       0x61    /* Where 'N' is the command byte & 0x1F. */
#define PS2_COMMAND_TEST_CONTROLLER    0xAA    /* Test PS/2 Controller. */
#define PS2_COMMAND_TEST_PORT1         0xAB    /* Test first PS/2 port. */
#define PS2_COMMAND_DEBUG_DUMP         0xAC    /* Dump all bytes of the internal RAM. */
#define PS2_COMMAND_DISABLE_PORT1      0xAD    /* Disable the device on PS/2 port 1. */
#define PS2_COMMAND_ENABLE_PORT1       0xAE    /* Enable the device on PS/2 port 1. */
#define PS2_COMMAND_DISABLE_PORT2      0xA7    /* Disable the device on PS/2 port 2. */
#define PS2_COMMAND_ENABLE_PORT2       0xA8    /* Enable the device on PS/2 port 2. */
#define PS2_COMMAND_TEST_PORT2         0xA9    /* Test second PS/2 port. */
#define PS2_COMMAND_READ_CONFIG        0xD0    /* Read controller output port. */
#define PS2_COMMAND_WRITE_CONFIG       0xD1    /* Send the next data byte to the Controller Output Port. */
#define PS2_COMMAND_WRITE_PORT1_OUTPUT 0xD2    /* Send the next data byte to PS/2 port 1 output buffer. */
#define PS2_COMMAND_WRITE_PORT2_OUTPUT 0xD3    /* Send the next data byte to PS/2 port 2 output buffer. */
#define PS2_COMMAND_WRITE_PORT2_INPUT  0xD4    /* Send the next data byte as a command for port 2. */
#define PS2_COMMAND_RESET_CPU          0xFE    /* Tie the reset line from the PS/2 controller to the CPU high. */

/* PS/2 controller response bytes. */
#define PS2_RESPONSE_PORT_TEST_PASS    0x00
#define PS2_RESPONSE_CLOCK_STUCK_LOW   0x01
#define PS2_RESPONSE_CLOCK_STUCK_HIGH  0x02
#define PS2_RESPONSE_DATA_STUCK_LOW    0x03
#define PS2_RESPONSE_DATA_STUCK_HIGH   0x04
#define PS2_RESPONSE_TEST_PASS         0x55
#define PS2_RESPONSE_TEST_FAIL         0xFC

void PS2SendData(uint8_t data);
void PS2SendCommand(uint8_t command);
void PS2WaitInputBuffer();
void PS2WaitOutputBuffer();
uint8_t PS2ReadData();
uint8_t PS2ReadStatus();
void SetupA20();
void SetupPS2();

#endif /* __KEYBOARD_H__ */

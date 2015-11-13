#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include <types.h>

void PS2SendData(uint8_t data);
void PS2SendCommand(uint8_t command);

uint8_t PS2ReadData();
uint8_t PS2ReadStatus();

void PS2DisableDevices();
void PS2EnableDevices();

void SetupPS2();

#endif /* __KEYBOARD_H__ */
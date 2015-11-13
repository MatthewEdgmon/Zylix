#ifndef __PS2KEYBOARD_H__
#define __PS2KEYBOARD_H__

#include <devices/ps2.h>

void PS2KeyboardEcho();
void PS2KeyboardSelfTest(); 
void PS2KeyboardEnableScanning();
void PS2KeyboardDisableScanning();

#endif /* __PS2KEYBOARD_H__ */
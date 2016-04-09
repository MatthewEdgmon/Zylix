#ifndef __CMOS_H__
#define __CMOS_H__

#include <stdint.h>

int CMOSIsUpdateInProgress();
int CMOSIsBatteryDead();
void CMOSReadRTC();

uint16_t CMOSGetYear();
uint16_t CMOSGetMonth();
uint16_t CMOSGetDay();
uint16_t CMOSGetHours();
uint16_t CMOSGetMinutes();
uint16_t CMOSGetSeconds();

char* CMOSGetDateAndTimeString();

int RTCHandlerIRQ();

void SetupRTC();

#endif /* __CMOS_H__ */

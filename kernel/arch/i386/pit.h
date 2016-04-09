#ifndef __PIT_H__
#define __PIT_H__

#include <stdint.h>

#include <arch/registers.h>

void PITSpeakerPlaySound();
void PITSetupTimer(uint32_t frequency);
int PITHandlerIRQ(registers_t* registers);

void SetupPIT();

#endif /* __PIT_H__ */

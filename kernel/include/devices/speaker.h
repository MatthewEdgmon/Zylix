#ifndef __SPEAKER_H__
#define __SPEAKER_H__

#include <libc/stdint.h>

void SpeakerPlaySound(uint32_t frequency);
void SpeakerNoSound();
void SpeakerBeep();

#endif /* __SPEAKER_H__ */

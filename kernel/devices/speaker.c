#include <devices/speaker.h>

#include <arch/IO.h>
#include <common.h>

#include <libc/stdint.h>

void SpeakerPlaySound(uint32_t frequency) {
    uint32_t divisor;
    uint8_t temp;

    /* Set the PIT to the frequency. */
    outb(0x43, 0xB6);
    outb(0x42, (uint8_t) (divisor));
    outb(0x42, (uint8_t) (divisor >> 8));

    /* Play the sound using the PC speaker. */
    temp = inb(0x61);
    if(temp != (temp | 3)) {
        outb(0x61, temp | 3);
    }
}

void SpeakerNoSound() {
    uint8_t temp;
    temp = inb(0x61) & 0xFC;
    outb(0x61, temp);
}

void SpeakerBeep() {
    SpeakerPlaySound(1000);
    SpeakerNoSound();
}
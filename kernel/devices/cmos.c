/**
 * Note: due to the hacky nature of the OS, CMOS /wiritng/ is not recomended. Could brick your motherboard.
 */

#include <terminal.h>

#include <arch/io.h>

/* Changed every year, in order to support CMOS without century registers. */
#define CMOS_CURRENT_YEAR         2016

#define CMOS_ADDRESS_PORT         0x70
#define CMOS_DATA_PORT            0x71

/* http://www.bioscentral.com/misc/cmosmap.htm */
/* TODO: Century register is dubious, parse ACPI to confirm existence. */
#define CMOS_REGISTER_SECONDS     0x00      /* Contains the seconds value of time. */
#define CMOS_REGISTER_SEC_ALARM   0x01      /* Contains the seconds value of the RTC alarm. */
#define CMOS_REGISTER_MINUTES     0x02      /* Contrains the minutes value of time. */
#define CMOS_REGISTER_MIN_ALARM   0x03      /* Contains the minutes value of the RTC alarm. */
#define CMOS_REGISTER_HOURS       0x04      /* Contains the hours value of time. */
#define CMOS_REGISTER_HOR_ALARM   0x05      /* Contains the hours value of the RTC alarm. */
#define CMOS_REGISTER_DAY_WEEK    0x06      /* Contrains the current day of the week (dubious). */
#define CMOS_REGISTER_DAY         0x07      /* Contains the day value of current date. */
#define CMOS_REGISTER_MONTH       0x08      /* Contains the month value of current date. */
#define CMOS_REGISTER_YEAR        0x09      /* Contains the year value of current date. */
#define CMOS_REGISTER_STATUSA     0x0A      /* Status register A. */
#define CMOS_REGISTER_STATUSB     0x0B      /* Status register B. */
#define CMOS_REGISTER_STATUSC     0x0C      /* Status register C. */
#define CMOS_REGISTER_STATUSD     0x0D      /* Status register D. */
#define CMOS_REGISTER_DIAGNOSTIC  0x0E      /* Diagnostic register. */
#define CMOS_REGISTER_SHUTDOWN    0x0F      /* CMOS shutdown status. */
#define CMOS_REGISTER_FLOPPY      0x10      /* Floppy disk drive types. */
#define CMOS_REGISTER_HARD        0x12      /* Hard disk drive types. */
#define CMOS_REGISTER_EQUIPMENT   0x14      /* Installed equipment. */
#define CMOS_REGISTER_CENTURY     0x48      /* Century register (dubious). */

uint16_t seconds;
uint16_t minutes;
uint16_t hours;
uint16_t day;
uint16_t month;
uint16_t year;

uint32_t boot_time;
uint32_t current_time;

uint16_t BCDToBinary(bcd) {
    return ((bcd & 0xF0) >> 1) + ((bcd & 0xF0) >> 3) + (bcd & 0xF);
}

/**
 * Dumps all 128 bytes of the CMOS to values[].
 */
void CMOSDumpValues(uint16_t* values) {
    uint16_t index;
    for(index = 0; index < 128; ++index) {
        while(CMOSIsUpdateInProgress()) {
	        outb(CMOS_ADDRESS_PORT, index);
		    values[index] = inb(CMOS_DATA_PORT);
        }
    }
}

uint8_t CMOSReadRegister(uint16_t cmos_register) {
    outb(CMOS_ADDRESS_PORT, cmos_register);
    return inb(CMOS_DATA_PORT);
}

/**
 * Returns zero if the CMOS is changing the time.
 */
int CMOSIsUpdateInProgress() {
    outb(CMOS_ADDRESS_PORT, CMOS_REGISTER_STATUSA);
    return inb(CMOS_DATA_PORT) & 0x80;
}

int CMOSIsBatteryDead() {
    outb(CMOS_ADDRESS_PORT, CMOS_REGISTER_STATUSD);
    return inb(CMOS_DATA_PORT) & 0x80;
}

/**
 * Reads all the values of the RTC in the CMOS.
 */
void CMOSReadRTC() {

    uint16_t century;
    uint16_t last_seconds;
    uint16_t last_minutes;
    uint16_t last_hours;
    uint16_t last_day;
    uint16_t last_month;
    uint16_t last_year;
    uint16_t last_century;
    uint16_t status_register_b;

    /* Do an initial read. */
    while(CMOSIsUpdateInProgress()) {
        seconds = CMOSReadRegister(CMOS_REGISTER_SECONDS);
        minutes = CMOSReadRegister(CMOS_REGISTER_MINUTES);
        hours = CMOSReadRegister(CMOS_REGISTER_HOURS);
        day = CMOSReadRegister(CMOS_REGISTER_DAY);
        month = CMOSReadRegister(CMOS_REGISTER_MONTH);
        year = CMOSReadRegister(CMOS_REGISTER_YEAR);
        century = CMOSReadRegister(CMOS_REGISTER_CENTURY);
    }

    /* Now verify if the values are the same. */
    do {
            /* Set the just read values as the last ones. */
            last_seconds = seconds;
            last_minutes = minutes;
            last_hours = hours;
            last_day = day;
            last_month = month;
            last_year = year;
            last_century = century;

            /* Make sure an update isn't in progress */
            while(CMOSIsUpdateInProgress());

            /* Read the (possibly updated) values again to verify. */
            seconds = CMOSReadRegister(CMOS_REGISTER_SECONDS);
            minutes = CMOSReadRegister(CMOS_REGISTER_MINUTES);
            hours = CMOSReadRegister(CMOS_REGISTER_HOURS);
            day = CMOSReadRegister(CMOS_REGISTER_DAY);
            month = CMOSReadRegister(CMOS_REGISTER_MONTH);
            year = CMOSReadRegister(CMOS_REGISTER_YEAR);
            century = CMOSReadRegister(CMOS_REGISTER_CENTURY);

      } while( (last_seconds != seconds) || (last_minutes != minutes) || (last_hours != hours) ||
               (last_day != day) || (last_month != month) || (last_year != year) ||
               (last_century != century) );

    /* Read the B status register to determine time format. */
    status_register_b = CMOSReadRegister(CMOS_REGISTER_STATUSB);

    /* If we're in BCD format, convert. */
    if(!(status_register_b & 0x04)) {
        seconds = BCDToBinary(seconds);
        minutes = BCDToBinary(minutes);
        hours = BCDToBinary(hours);
        day = BCDToBinary(day);
        month = BCDToBinary(month);
        year = BCDToBinary(year);
        century = BCDToBinary(century);
    }

    /* If we're in 24 hour clock, convert. */
    if((status_register_b & 0x02) && (hours & 0x80)) {
        hours = ((hours & 0x7F) + 12) % 24;
    }

    /* Calculate the 4 digit year. */
    year += century * 100;

    return;
}

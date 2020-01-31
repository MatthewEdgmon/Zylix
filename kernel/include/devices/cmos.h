/**
 * cmos.h - CMOS
 *
 * This file is part of Zylix.
 *
 * Zylix is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Zylix is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Zylix.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __CMOS_H__
#define __CMOS_H__

#include <arch/registers.h>

/* Changed every year, in order to support CMOS without century registers. */
#define CMOS_CURRENT_YEAR         2020

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

#include <stdint.h>

uint8_t CMOSIsUpdateInProgress();
uint8_t CMOSIsBatteryDead();
void CMOSReadRTC();

uint16_t CMOSGetYear();
uint16_t CMOSGetMonth();
uint16_t CMOSGetDay();
uint16_t CMOSGetHours();
uint16_t CMOSGetMinutes();
uint16_t CMOSGetSeconds();

int RTCHandlerIRQ(cpu_registers_t* registers);

void SetupRTC();

#endif /* __CMOS_H__ */

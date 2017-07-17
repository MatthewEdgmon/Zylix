/**
 * ps2mouse.h - PS/2 mouse driver.
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

#ifndef __PS2MOUSE_H__
#define __PS2MOUSE_H__

/* PS/2 Data port mouse commands. */
#define PS2_MOUSE_STATUS_REQUEST         0xE9
#define PS2_MOUSE_READ_DATA              0xEB
#define PS2_MOUSE_RESET_WRAP_MODE        0xEC
#define PS2_MOUSE_SET_WRAP_MODE          0xEE
#define PS2_MOUSE_SET_REMOTE_MODE        0xF0
#define PS2_MOUSE_GET_DEVICE_ID          0xF2
#define PS2_MOUSE_SET_SAMPLE_RATE        0xF3
#define PS2_MOUSE_ENABLE_DATA_REPORT     0xF4
#define PS2_MOUSE_DISABLE_DATA_REPORT    0xF5
#define PS2_MOUSE_SET_DEFAULTS           0xF6
#define PS2_MOUSE_RESEND                 0xFE
#define PS2_MOUSE_RESET_SELF_TEST        0xFF    /* Reset and start self test. */

/* PS/2 Keyboard special response bytes. */
#define PS2_MOUSE_RESPONSE_ACK           0xFA    /* Command acknowledged. */

void SetupPS2Mouse();

void PS2MouseHandler();

#endif /* __PS2MOUSE_H__ */

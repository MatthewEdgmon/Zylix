#ifndef __PS2MOUSE_H__
#define __PS2MOUSE_H__

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

void SetupPS2Mouse();

void PS2MouseHandler();

#endif /* __PS2MOUSE_H__ */
#ifndef __REBOOT_H__
#define __REBOOT_H__

int reboot() {
    return syscall_0arg(SYSCALL_REBOOT);
}

#endif /* __REBOOT_H__ */

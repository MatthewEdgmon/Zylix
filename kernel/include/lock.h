#ifndef __LOCK_H__
#define __LOCK_H__

#include <libc/stdint.h>

void SetupTicketLock();
uint16_t TicketLockAcquire();
void TicketLockRelease();

#endif /* __LOCK_H__ */

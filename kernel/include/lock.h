#ifndef __LOCK_H__
#define __LOCK_H__

#include <stdint.h>

#define LOCK_USE_TICKET_LOCK

#ifdef LOCK_USE_TICKET_LOCK
#define LockAcquire TicketLockAcquire
#define LockRelease TicketLockRelease
#define SetupLocks  TicketLockSetup
#elif LOCK_USE_TEST_SET
#define LockAcquire TestSetLockAcquire
#define LockRelease TestSetLockRelease
#define SetupLocks  TestSetLockSetup
#endif

/* Ticket Lock. */
void TicketLockAcquire();
void TicketLockRelease();
void TicketLockSetup();

/* Test and Set. */
void TestSetLockAcquire();
void TestSetLockRelease();
void TestSetLockSetup();

#endif /* __LOCK_H__ */

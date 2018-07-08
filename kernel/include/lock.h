/**
 * lock.h - Routines for data locking.
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

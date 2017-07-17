/**
 * lock.c - Atomic locking routines.
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

#include <lock.h>
#include <logging.h>

uint32_t test_set_lock[2];

/* Atomic xchg. */
static inline int arch_atomic_swap(volatile int* x, int v) {
	__asm__("xchg %0, %1" : "=r"(v), "=m"(*x) : "0"(v) : "memory");
	return v;
}

/* Atomic move. */
static inline void arch_atomic_store(volatile int* p, int x) {
	__asm__("movl %1, %0" : "=m"(*p) : "r"(x) : "memory");
}

/* Atomic increment. */
static inline void arch_atomic_inc(volatile int* x) {
	__asm__("lock; incl %0" : "=m"(*x) : "m"(*x) : "memory");
}

/* Atomic decrement. */
static inline void arch_atomic_dec(volatile int* x) {
	__asm__("lock; decl %0" : "=m"(*x) : "m"(*x) : "memory");
}

/**
 * Ticket lock
 */

 void TicketLockAcquire() {

 }

 void TicketLockRelease() {

 }

 void TicketLockSetup() {
     test_set_lock[0] = 0;
     test_set_lock[1] = 0;
 }

/**
 * The test-and-set lock
 */

 void TestSetLockAcquire() {

 }

 void TestSetLockRelease() {

 }

 void TestSetLockSetup() {
     test_set_lock[0] = 0;
     test_set_lock[1] = 0;
 }

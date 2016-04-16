#include <lock.h>
#include <logging.h>

uint32_t ticket_lock_next_ticket = 0;
uint32_t ticket_lock_now_serving = 0;

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
 * https://en.wikipedia.org/wiki/Ticket_lock
 */

void TicketLockAcquire() {

}

void TicketLockRelease() {

}

void TicketLockSetup() {
    ticket_lock_now_serving = 0;
    ticket_lock_next_ticket = 0;
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

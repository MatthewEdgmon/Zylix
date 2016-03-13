/**
 * My first attempt at locks. Trying out ticket queue lock system.
 * https://en.wikipedia.org/wiki/Ticket_lock
 */
#include <lock.h>

uint16_t ticket_lock_next_ticket = 0;
uint16_t ticket_lock_now_serving = 0;

void SetupTicketLock() {
    ticket_lock_next_ticket = 0;
    ticket_lock_now_serving = 0;
}

uint16_t TicketLockAcquire() {
    return ticket_lock_next_ticket++;
}

void TicketLockRelease() {
    ticket_lock_now_serving++;
}

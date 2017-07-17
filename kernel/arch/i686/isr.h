/**
 * isr.h - i686 Interrupt Service Routines
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

#ifndef __ISR_H__
#define __ISR_H__

/* ISR numbers. */
#define ISR_DIVIDE_BY_ZERO 0

#define ISR_PAGE_FAULT 19
#define ISR_SYSCALL 99

#define SYSCALL_VECTOR 0x63

void ISRInstallHandler(size_t isrs, irq_handler_t handler);
void ISRUninstallHandler(size_t isrs);
void ISRFaultHandler(struct registers *regs);

void SetupISR();

#endif /* __ISR_H__ */

/**
 * pic.h - i686 Programmable Interrupt Controller
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

#ifndef __PIC_H__
#define __PIC_H__

#include <stdint.h>

#include <arch/interrupts.h>
#include <arch/registers.h>

void PICDisableInterrupts();
void PICEnableInterrupts();
void PICResumeInterrupts();
void PICInstallIRQHandler(size_t irq, irq_handler_chain_t handler);
void PICUninstallIRQHandler(size_t irq);
void PICHandlerIRQ(cpu_registers_t* regs);
void PICSetMask(uint16_t irq);
void PICClearMask(uint16_t irq);
void PICRemap(int first_offset, int second_offset);
void PICSendEOI(unsigned int irq);
void PICDisable();
void PICSetupTimer(uint32_t frequency);
void SetupPIC();

#endif /* __PIC_H__ */

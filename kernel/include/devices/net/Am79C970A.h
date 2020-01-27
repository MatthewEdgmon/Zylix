/**
 * AM79C970A.h - AMD PCnet-PCI II Network Driver
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

#ifndef __AM79C970A_H__
#define __AM79C970A_H__

#define AM79C970A_PCI_VENDOR_ID     0x1022
#define AM79C970A_PCI_DEVICE_ID     0x2000
#define AM79C970A_PCI_DEVICE_ID_ALT 0x2000

int SetupAm79C970A();

#endif /* __AM79C970A_H__ */

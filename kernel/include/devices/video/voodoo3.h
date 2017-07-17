/**
 * voodoo3.h - 3DFx Voodoo 3 driver.
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

#ifndef __VOODOO3_H__
#define __VOODOO3_H__

#include <stdint.h>

#define VOODOO3_REGISTER_STATUS 0x00
#define VOODOO3_REGISTER_VGA

/* These values are sent to the VGA index register to select the VGA register. */
#define VOODOO3_VGA_INDEX_CRTC_INDEX        0x0
#define VOODOO3_VGA_INDEX_HORIZONTAL
#define VOODOO3_VGA_LATCH_READ_BACK         0x22

/* These values are sent to the CRTC index register to select the CRTC register. */

void SetupVoodoo3();

#endif /* __VOODOO3_H__ */

/**
 * browser.c - Built-in file explorer.
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

#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include <arch/io.h>
#include <arch/interrupts.h>

#include <devices/ps2keyboard.h>

#include <menu/monitor.h>
#include <terminal.h>
#include <vga.h>

void BrowserMain() {
    printf("Test.\n");
}

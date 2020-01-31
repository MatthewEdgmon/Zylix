/**
 * boot.s - i686 multiboot Entry Point
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

/* Adapted from http://www.gnu.org/software/grub/manual/multiboot/html_node/boot_002eS.html#boot_002eS */

# Multiboot magic number.
.set MULTIBOOT_HEADER_MAGIC,      0x1BADB002
# Align loaded modules on page boundaries.
.set MB_FLAG_PAGE_ALIGN,          1 << 0
# Provde a memory map.
.set MB_FLAG_MEMORY_INFO,         1 << 1
# Please set up graphical mode for us.
.set MB_FLAG_GRAPHICS,            1 << 2
# Set the flags.
.set MULTIBOOT_HEADER_FLAGS,      MB_FLAG_PAGE_ALIGN | MB_FLAG_MEMORY_INFO | MB_FLAG_GRAPHICS
# Multiboot checksum.
.set MULTIBOOT_HEADER_CHECKSUM,   -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)

.section .multiboot
.align 4

# Multiboot header lives here.
.long MULTIBOOT_HEADER_MAGIC
.long MULTIBOOT_HEADER_FLAGS
.long MULTIBOOT_HEADER_CHECKSUM
# ELF executable info.
.long 0x00000000 /* header_addr */
.long 0x00000000 /* load_addr */
.long 0x00000000 /* load_end_addr */
.long 0x00000000 /* bss_end_addr */
.long 0x00000000 /* entry_addr */

# Request linear graphics mode.
.long 0x00000000
.long 0
.long 0
.long 32

# Reserve a stack for the initial thread.
.section .stack, "aw", @nobits
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

# The kernel entry point.
.code32
.section .text

.global _start
.type _start, @function

.extern main
.type main, @function

# The kernel entry point.
_start:
	# Setup the stack.
	mov $stack_top, %esp

	# Make sure our stack is 16-byte aligned.
    and $-16, %esp

	# Setup arguments for main.
    pushl %esp # Stack
    pushl %eax # Multiboot header magic.
    pushl %ebx # Multiboot information structure.

	# Disable interrupts.
	cli

	# Transfer control to the main kernel.
	call main

	# Hang if main unexpectedly returns.
	cli

hang:
    # Keep jumping back in case NMI interrupts HLT.
	hlt
	jmp hang

.size _start, . - _start

.set MB_MAGIC,              0x1BADB002		     # 'Magic number' lets bootloader find the header.
.set MB_FLAG_PAGE_ALIGN,    1 << 0			      # Align loaded modules on page boundaries.
.set MB_FLAG_MEMORY_INFO,   1 << 1			  	  # Provide memory map.
.set MB_FLAG_GRAPHICS,      1 << 2
.set MB_FLAGS,              MB_FLAG_PAGE_ALIGN | MB_FLAG_MEMORY_INFO | MB_FLAG_GRAPHICS
.set MB_CHECKSUM,           -(MB_MAGIC + MB_FLAGS) # checksum of above, to prove we are multiboot

.section .multiboot
.align 4

# Multiboot header lives here.
.long MB_MAGIC
.long MB_FLAGS
.long MB_CHECKSUM
.long 0x00000000 /* header_addr */
.long 0x00000000 /* load_addr */
.long 0x00000000 /* load_end_addr */
.long 0x00000000 /* bss_end_addr */
.long 0x00000000 /* entry_addr */

/* Request linear graphics mode */
.long 0x00000000
.long 0
.long 0
.long 32

# Reserve a stack for the initial thread.
.section .stack, "aw", @nobits
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

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
    pushl %ebx # Multiboot header pointer.

	# Disable interrupts.
	cli

	# Transfer control to the main kernel.
	call main

	# Hang if main unexpectedly returns.
	cli

hang:
	hlt
	jmp hang

.size _start, . - _start

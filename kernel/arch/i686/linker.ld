/* The bootloader will look at this image and start execution at the symbol
   designated at the entry point. */

/* OUTPUT_FORMAT(elf32-i386) */
OUTPUT_FORMAT(i686-pc-zylix)
ENTRY(_start)

/* Tell where the various sections of the object files will be put in the final
   kernel image. */
SECTIONS
{
	/* Begin putting sections at 1 MiB, a conventional place for kernels to be
	   loaded at by the bootloader. */
	. = 1M;
    phys = .;

	/* First put the multiboot header, as it is required to be put very early
	   early in the image or the bootloader won't recognize the file format.
	   Next we'll put the .text section. */
	.text BLOCK(4K) : ALIGN(4K)
	{
        code = .;
		*(.multiboot)
		*(.text)
	}

	/* Read-only data. */
	.rodata BLOCK(4K) : ALIGN(4K)
	{
		*(.rodata)
	}

	/* Read-write data (initialized) */
	.data BLOCK(4K) : ALIGN(4K)
	{
        data = .;
		*(.data)
		*(.symbols)
	}

	/* Read-write data (uninitialized) and stack */
	.bss BLOCK(4K) : ALIGN(4K)
	{
        bss = .;
		*(COMMON)
		*(.bss)
		*(.bootstrap_stack)
	}

    end = .;

    /* Get rid of useless stuff GCC puts in our kernel. */
	/DISCARD/ :
	{
		*(.comment)
		*(.note.gnu.build-id)
	}
}

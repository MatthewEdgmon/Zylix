.section text
.align 4

.global Virtual8086
.type Virtual8086, @function

Virtual8086:
    cli
    /* We need a 16-bit GDT. */

    /* Save the protected mode cr0. */
    mov %cr0, %eax
    /* Disable paging and enable 16-bit pmode. */
    and $0x7FFFFFFE, %eax
    mov %cr0, %eax

    /* Perform a far jump to set CS. */
    jmp EnterRealMode

EnterRealMode:
    /* Reset segment registers to 0. */
    movw $0, %ax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs
    movw %ax, %ss
    sti

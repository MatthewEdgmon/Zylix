.section .text
.align 4

.global FlushGDT
.type FlushGDT, @function

FlushGDT:
    /* Load GDT */
    mov 4(%esp), %eax
    lgdt (%eax)

    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %ss

    ljmp $0x08, $.flush
.flush:
    ret

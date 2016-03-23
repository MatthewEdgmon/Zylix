.section .text
.align 4

.global LoadGDT
.type LoadGDT, @function

LoadGDT:
    mov 4(%esp), %eax
    lgdt (%eax)

ReloadSegments:
    /* 0x10 points to the new data selector. */
    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %ss

    ljmp $0x08, $.flush
.flush:
    ret

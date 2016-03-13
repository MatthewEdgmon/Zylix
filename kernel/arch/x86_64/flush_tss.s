.section .text
.align 4

.global FlushTSS
.type FlushTSS, @function

FlushTSS:
    mov $0x2B, %ax
    ltr %ax
    ret

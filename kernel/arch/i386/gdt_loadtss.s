.section .text
.align 4

.global LoadTSS
.type LoadTSS, @function

LoadTSS:
    mov $0x2B, %ax
    ltr %ax
    ret

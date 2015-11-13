.section text
.align 4

.global FlushIDT
.type FlushIDT, @function

FlushIDT:
    mov 4(%esp), %eax
    lidt (%eax)
    ret

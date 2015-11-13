.align 4

.global LoadIDT
.type LoadIDT, @function

LoadIDT:
    mov 4(%esp), %eax
    lidt (%eax)
    ret

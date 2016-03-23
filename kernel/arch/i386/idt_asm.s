.section .text
.align 4

.global LoadIDT
.type LoadIDT, @function

# Takes a pointer to the IDT
LoadIDT:
    mov 4(%esp), %eax
    lidt (%eax)
    ret

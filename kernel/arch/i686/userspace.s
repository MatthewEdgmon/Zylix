.section .text
.align 4

.global UserspaceReturn
.type UserspaceReturn, @function

UserspaceReturn:
    pop %gs
    pop %fs
    pop %es
    pop %ds
    popa
    add $8, %esp
    iret

.global UserspaceJump
.type UserspaceJump, @function

UserspaceJump:

    /* Request ring3 */
    orl $0x200, %eax
    pushl %eax
    pushl $0x1B

    iret
    pushl %ebp
    ret

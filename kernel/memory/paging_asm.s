.section .text
.align 4

.global PagingLoadDirectory
.type PagingLoadDirectory, @function

/* Load the address of the page directory from EAX into CR3. */
PagingLoadDirectory:
    push %ebp
    mov 8(%esp), %eax
    mov %eax, %cr3
    mov %ebp, %esp
    pop %ebp
    ret

.global PagingEnable
.type PagingEnable, @function

/* Set the 32nd bit in CR0 to enable paging. */
PagingEnable:
    push %ebp
    mov %esp, %ebp
    mov %cr0, %eax
    or $0x80000000, %eax
    mov %eax, %cr0
    mov %ebp, %esp
    pop %ebp
    ret

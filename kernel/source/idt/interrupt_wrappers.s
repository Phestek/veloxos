.file           "interrupt_wrappers.s"
.intel_syntax   noprefix

.macro  push_regs
        push    rsp
        push    rax
        push    rbx
        push    rcx
        push    rdx
        push    rsi
        push    rdi
        push    rbp
        push    r8
        push    r9
        push    r10
        push    r11
        push    r12
        push    r13
        push    r14
        push    r15
.endm

.macro  pop_regs
        pop     r15
        pop     r14
        pop     r13
        pop     r12
        pop     r11
        pop     r10
        pop     r9
        pop     r8
        pop     rbp
        pop     rdi
        pop     rsi
        pop     rdx
        pop     rcx
        pop     rbx
        pop     rax
.endm

.global int_00_division_error_wrapper
.type   int_00_division_error_wrapper, @function
.text
int_00_division_error_wrapper:
        push_regs
        mov     rdi,    rsp
        call    int_00_division_error_handler@PLT
        pop_regs
        add     rsp,    8
        iretq


bits    16
org     0x0000

start:
        call    stage2_enable_a20

        mov     ax,     0x2000
        mov     ds,     ax
        mov     es,     ax

        mov     ax,     0x1F00
        mov     ss,     ax
        xor     sp,     sp

        cli

        lgdt    [gdt32_descriptor]

        mov     eax,    cr0
        or      eax,    1
        mov     cr0,    eax

        jmp     dword   0x00000008:(0x00020000 + enter_protected_mode)

%include "source/bootloader/stage2_enable_a20.asm"
%include "source/bootloader/stage2_gdt.asm"

enter_protected_mode:
        bits    32

        mov     ax,     0x0010
        mov     ds,     ax
        mov     es,     ax
        mov     ss,     ax

        mov     eax,    pml4 - $$ + 0x00020000
        mov     cr3,    eax

        mov     eax,    cr4
        or      eax,    1 << 5
        mov     cr4,    eax

        mov     ecx,    0xC0000080      ; EFER
        rdmsr
        or      eax,    1 << 8
        wrmsr

        mov     eax,    cr0
        or      eax,    1 << 31
        mov     cr0,    eax

        lgdt    [gdt64_descriptor + 0x00020000]
        jmp     dword   0x0008:(0x00020000 + enter_long_mode)

%include "source/bootloader/stage2_paging.asm"

enter_long_mode:
        bits    64

        mov     ax,     0x0010
        mov     ds,     ax
        mov     es,     ax
        mov     ss,     ax

elf_loader:
        mov     rsi,    [0x00020000 + kernel + 0x20]
        add     rsi,    0x00020000 + kernel

        movzx   ecx,    word [0x00020000 + kernel + 0x38]

        cld

        ; Assumes that the linker always stores ELF header at first p_vaddr.
        xor     r14,    r14     ; First PT_LOAD p_vaddr.

.ph_loop:
        mov     eax,    [rsi + 0]
        cmp     eax,    1       ; If it's not PT_LOAD, ignore.
        jne     .next

        mov     r8,     [rsi + 0x00000008]      ; p_offset
        mov     r9,     [rsi + 0x00000010]      ; p_vaddr
        mov     r10,    [rsi + 0x00000020]      ; p_filesz
        mov     r11,    [rsi + 0x00000028]      ; p_memsz

        test    r14,    r14
        jnz     .skip
        mov     r14,    r9

.skip:
        ; Backup.
        mov     rbp,    rsi
        mov     r15,    rcx

        ; Zero memory.
        mov     rdi,    r9
        mov     rcx,    r11
        xor     al,     al
        rep     stosb

        ; Copy segment.
        lea     rsi,    [0x00020000 + kernel + r8d]
        mov     rdi,    r9
        mov     rcx,    r10
        rep     movsb

        ; Restore.
        mov     rcx,    r15
        mov     rsi,    rbp
.next:
        add     rsi,    0x38
        loop    .ph_loop

        ; Fix stack.
        mov     rsp,    0x0030F000

        ; Jump to EP
        mov     rdi,    r14
        mov     rax,    [0x00020000 + kernel + 0x18]
        call    rax

align 0x0200

kernel:

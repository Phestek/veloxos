bits    16
org     0x0000

start:
        mov     ax,     0x07E0
        mov     ds,     ax
        mov     es,     ax

        mov     ax,     0x07BF
        mov     ss,     ax
        xor     sp,     sp

        call    stage2_enable_a20

        cli
        lgdt    [gdt32_descriptor]
        mov     eax,    cr0
        or      eax,    1
        mov     cr0,    eax

        jmp     dword   0x0008:(0x7E00 + enter_protected_mode)

%include        "source/bootloader/stage2_enable_a20.asm"

enter_protected_mode:
        bits    32
        
        mov     ax,     0x10
        mov     ds,     ax
        mov     es,     ax
        mov     ss,     ax
        lea     eax,    [0xb8000]
        mov     dword   [eax],  0x9F4B9F4F

        jmp     $

enter_long_mode:
        bits    64
        jmp     $

gdt32_descriptor:
        dw      gdt32_end - gdt32_begin - 1
        dd      0x7E00 + gdt32_begin

align 0x04

gdt32_begin:
        ; Null segment.
        dd      0x0000
        dd      0x0000
        ; Code segment.
        dd      0xFFFF
        dd      (10 << 8) | (1 << 12) | (1 << 15) | (0xf << 16) | (1 << 22) | (1 << 23)
        ; Data segment.
        dd 0xFFFF
        dd      (2 << 8) | (1 << 12) | (1 << 15) | (0xf << 16) | (1 << 22) | (1 << 23)
        ; Null segment.
        dd      0x0000
        dd      0x0000
gdt32_end:


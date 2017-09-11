bits    16
org     0x0000

start:
        mov     ax,     0x07E0
        mov     ds,     ax
        mov     es,     ax

        mov     ax,     0x07BF
        mov     ss,     ax
        xor     sp,     sp

        ; Enable A20 line using Fast Gate.
        in      al,     0x92
        or      al,     0x02
        out     0x92,   al

        cli
        lgdt    [gdt32_descriptor]
        mov     eax,    cr0
        or      eax,    1
        mov     cr0,    eax

        jmp     dword   0x0008:(0x7E00 + enter_protected_mode)

enter_protected_mode:
        bits    32
        
        mov     ax,     0x10
        mov     ds,     ax
        mov     es,     ax
        mov     ss,     ax

        lea     eax,    [0xb8000]
  
        mov     dword   [eax],  0x9F4B9F4F
        jmp     $

gdt32_descriptor:
        dw      gdt32_end - gdt32_begin - 1
        dd      0x7E00 + gdt32_begin

times   32 - ($ - $$) % 32 \
        db      0x00

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


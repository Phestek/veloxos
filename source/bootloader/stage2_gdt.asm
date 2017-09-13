gdt32_descriptor:
        dw      gdt32_end - gdt32_begin - 1
        dd      0x00020000 + gdt32_begin

align   0x04

gdt32_begin:
        ; Null segment.
        dd      0x00000000
        dd      0x00000000
        ; Code segment.
        dd      0xFFFF
        dd      (10 << 8) | (1 << 12) | (1 << 15) | (0xf << 16) | (1 << 22) | (1 << 23)
        ; Data segment.
        dd      0xFFFF
        dd      (2 << 8) | (1 << 12) | (1 << 15) | (0xf << 16) | (1 << 22) | (1 << 23)
        ; Null segment.
        dd      0x00000000
        dd      0x00000000
gdt32_end:

gdt64_descriptor:
        dw      gdt64_end - gdt64_begin - 1
        dd      0x00020000 + gdt64_begin

align   0x08

gdt64_begin:
        ; Null segment
        dd 0, 0
        ; Code segment
        dd 0xffff  ; segment limit
        dd (10 << 8) | (1 << 12) | (1 << 15) | (0xf << 16) | (1 << 21) | (1 << 23)
        ; Data segment
        dd 0xffff  ; segment limit
        dd (2 << 8) | (1 << 12) | (1 << 15) | (0xf << 16) | (1 << 21) | (1 << 23)
        ; Null segment
        dd 0, 0
gdt64_end:


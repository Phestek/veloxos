align   0x1000

; Page Map Level 4.
pml4: 
        dq 1 | (1 << 1) | (pdpt - $$ + 0x20000)
        times   511 \
                dq 0x0000000000000000

; Page Directory Pointer Table.
pdpt:
        dq 1 | (1 << 1) | (pdt - $$ + 0x20000) 
        times   511 \
                dq 0x0000000000000000

; Page Directory Table.
pdt:
        ; This code maps first 4GB or RAM in flat mode.
        %assign i       0
        %rep    0x0800
                dq      0x200000 * i + 0x83
        %assign i       i + 1
        %endrep


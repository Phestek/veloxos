bits    16
org     0x2000

start:
        mov     ax,     0x2000
        mov     ds,     ax
        mov     es,     ax

        mov     ax,     0x1F00
        mov     ss,     ax
        xor     sp,     sp

        ; Enable A20 line using Fast Gate.
        in      al,     0x92
        or      al,     0x02
        out     0x92,   al

        mov     ah,     0x0E
        mov     al,     '%'
        int     0x10

        jmp     $


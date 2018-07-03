bits    16
org     0x7C00

jmp     word    start

start:
        ; Some BIOSes do not expose extensions if you don't ask for them first.
        mov     ah,     0x41    ; Procedure number - check for extensions.
        mov     bx,     0x55AA  ; Value required by a procedure.
        int     0x13

        ; If CF flag is set, procedure is not available.
        jc      .bios_not_supported

        ; If BH and BL weren't swapped, procedure is not available.
        cmp     bx,     0x55AA
        je      .bios_not_supported

        ; Last thing to check is bit 0 in CL register.
        bt      cx,     0x00
        jnc     .bios_not_supported

        ; Load rest of the system into memory.
        mov     ah,     0x42
        mov     si,     disk_address_packet
        int     0x13

        ; Jump to stage2.
        jmp     word    0x2000:0x0000

.bios_not_supported:
        ; TODO: Print error message.
        jmp     $

disk_address_packet:
        db      0x10        ; Size of the packet.
        db      0x00        ; Something with 'reserve' - should always be 0x00.
        dw      0xCCCC      ; Number of segments to load - will be set by a build script.
        ; Address to load rest of the system.
        dw      0x0000      ; Offset.
        dw      0x2000      ; Segment.
        ; Segment to start loading from.
        dq      0x0000000000000001

signature:
        %if $ - $$ > 510
            %fatal "stage1 code exceed 512 bytes."
        %endif

        times   510 - ($ - $$) \
                db      0x00
        dw      0xAA55


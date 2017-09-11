bits    16

stage2_enable_a20:
        ; Check if A20 is enabled. If not, unlock it.
        call    .check_a20
        jc      .enable_by_bios
        ret

.check_a20:
        ; Save data segment address.
        push    ds

        ; Set data segment at end of memory.
        mov     ax,     0xFFFF
        mov     ds,     ax

        ; Try to write at address 0x100500 (0xFFFF0 + 0x0510)
        mov     byte [ds:0x0510],       0xFF

        ; Restore data segment address.
        pop     ds

        ; Check if value under 0x0000:0x0500 is equal to the written one.
        mov     al,     byte [ds:0x0500]
        cmp     byte [ds:0x0500],       0xFF

        ; If diffrent then A20 is unlocked.
        jne     .check_a20_success

        ; A20 is disabled.
        sti
        ret

.check_a20_success:
        clc
        ret

.enable_by_bios:
        mov     ax,     0x2403
        int     0x15
        call    .check_a20
        jc      .enable_by_keyboard_controller

.enable_by_keyboard_controller:
        cli

        call    .wait_for_keyboard_input_ready

        ; Disable keyboard.
        mov     al,     0xAD
        out     0x64,   al

        call    .wait_for_keyboard_input_ready

        ; Ask for keyboard input.
        mov     al,     0xD0
        out     0x64,   al

        ; Wait for keyboard be ready to give response.
        call    .wait_for_keyboard_output_ready

        ; Read data from keyboard.
        in      al,     0x60
        push    ax

        call    .wait_for_keyboard_input_ready

        ; Ask for input write.
        mov     al,     0xD1
        out     0x64,   al

        call    .wait_for_keyboard_input_ready

        pop     ax

        ; Set AL's second bit.
        or      al,     2
        out     0x60,   al

        call    .wait_for_keyboard_input_ready
        
        ; Enable keyboard.
        call    .wait_for_keyboard_input_ready

        sti

        call    .check_a20
        jc      .enable_by_fast_gate
        ret

.enable_by_fast_gate:
        in      al, 0x92
        test    al, 2
        jnz     .enable_by_fast_gate_success
        or      al, 2
        and     al, 0xFE
        out     0x92, al

.enable_by_fast_gate_success:
        call    .check_a20
        jc      .enable_a20_error       ; No A20 :(
        ret

.enable_a20_error:
        ; TODO: Print error message.
        jmp     $

.wait_for_keyboard_input_ready:
        in      al,     0x64
        test    al,     2
        jnz     .wait_for_keyboard_input_ready
        ret
        
.wait_for_keyboard_output_ready:
        in      al,     0x64
        test    al,     1
        jz      .wait_for_keyboard_output_ready
        ret


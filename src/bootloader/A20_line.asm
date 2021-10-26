[bits 16]
; check if A20 is enabled
check_A20:
    pushf                          ; Save registers that
    push ds                        ; we are going to
    push es                        ; overwrite.
    push di
    push si

    cli                            ; No interrupts, please

    xor ax, ax                     ; Set es:di = 0000:0500
    mov es, ax
    mov di, 0x0500

    mov ax, 0xffff                 ; Set ds:si = ffff:0510
    mov ds, ax
    mov si, 0x0510

    mov al, byte es:[di]       ; Save byte at es:di on stack.
    push ax                        ; (we want to restore it later)

    mov al, byte ds:[si]       ; Save byte at ds:si on stack.
    push ax                        ; (we want to restore it later)

    mov byte es:[di], 0x00     ; [es:di] = 0x00
    mov byte ds:[si], 0xFF     ; [ds:si] = 0xff

    cmp byte es:[di], 0xFF     ; Did memory wrap around?

    pop ax
    mov byte ds:[si], al       ; Restore byte at ds:si

    pop ax
    mov byte es:[di], al       ; Restore byte at es:di

    mov ax, 0
    je check_A20_exit         ; If memory wrapped around, return 0.

    mov ax, 1                      ; else return 1.


; function that just restores all the registers after check for enable
check_A20_exit:
    pop si
    pop di
    pop es
    pop ds
    popf
    ret

enable_A20_fast: ; enable the a20 line with the fast gate
    in al, 0x92
    or al, 2
    out 0x92, al
    ret

; enable A20 line trought the BIOS interupt
enable_A20_bios:
    mov ax, 0x2401
    int 0x15
    ret

; enable A20 trough keyboard line send command trough keyboard line
enable_A20_command:
    xor ax, ax
    in al, 0x64
    test al, 2
    jnz enable_A20_command
    ret

; get data from A20 keyboard line
enable_A20_data:
    xor ax, ax
    in al, 0x64
    test al, 1
    jz enable_A20_data
    ret

enable_A20_keyboard:
    cli ; disable interupts

    call enable_A20_command ; when controller is ready for command
    mov al, 0xad ; send 0xad (disable keyboard)
    out 0x64, al

    call enable_A20_command
    mov al, 0xd0 ; send command 0xd0 (read for interupt)
    out 0x64, al

    call enable_A20_data ; when controller had data
    in al, 0x60 ; read input from keyboard
    push eax ; ... and save it

    call enable_A20_command
    mov al, 0xd1 ; set comamnd 0xd1 (write to output)
    out 0x64, al

    call enable_A20_command
    pop eax ; write intput back, with bit 2 set
    or al, 2
    out 0x60, al

    call enable_A20_command
    mov al, 0xae ; write command 0xae (enable keyboard)
    out 0x64, al

    call enable_A20_command

    sti
    ret

A20_fail_str:
    db 'A20 has failed to enable', 0x0a, 0x0d, 0

A20_done_str:
    db 'A20 enabled', 0x0a, 0x0d, 0

A20_fail:
    mov si, A20_fail_str
    call print

    jmp $

A20_done:
    mov si, A20_done_str
    call print

    ret

enable_A20:
    call check_A20
    cmp ax, 0
    jne A20_done

    call enable_A20_fast
    call check_A20
    cmp ax, 0
    jne A20_done

    call enable_A20_bios
    call check_A20
    cmp ax, 0
    jne A20_done

    call enable_A20_keyboard
    call check_A20
    cmp ax, 0
    jne A20_done

    jmp A20_fail
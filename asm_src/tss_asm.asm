global tss_flush
global asm_switch

tss_flush:
    mov ax, 0x28
    ltr ax
    ret



asm_switch:
    cli
    mov ax, 0x23
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov eax, esp
    push 0x23
    push eax
    pushf
    pop eax
    or eax, 0x200
    push eax
    mov eax, 0x1B 
    push eax
    ;mov ax, sp
    ;add ax, 3
    ;push ax
    ret

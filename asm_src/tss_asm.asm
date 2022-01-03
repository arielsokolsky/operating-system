global tss_flash
global asm_switch

tss_flush:
    mov ax, 0x2B
    lrt ax
    ret



asm_switch:
    cli
    mov ax 0x23
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov eax, esp
    pushl 0x23
    pushl eax
    pushf
    pop eax
    or eax, 0x200
    push eax

    pushl 0x1B
    ret

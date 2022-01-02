global flush_tss


flush_tss:
    mov ax, 0x2c
    ltr ax
    ret
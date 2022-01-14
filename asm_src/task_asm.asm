global to_esp
global flush_tlb
to_esp:
    pop eax
    jmp eax

flush_tlb:
    mov eax, cr3
    mov cr3, eax
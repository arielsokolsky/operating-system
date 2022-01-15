global read_eip
global flush_tlb
read_eip:
    pop eax
    jmp eax

flush_tlb:
    mov eax, cr3
    mov cr3, eax
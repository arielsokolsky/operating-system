global insw
global outsw

insw:
    push   edi
    mov    edx, [esp + 8] 
    mov    esi, [esp + 12]
    mov    ecx, [esp + 16]

    xor eax, eax

insw_startLoop:
    cmp    ecx, eax
    je      insw_end

    insw

    inc    eax
    jmp     insw_startLoop

insw_end:
    pop    edi
    ret

outsw:
    push   esi
    mov    edx, [esp + 8]
    mov    esi, [esp + 12]
    mov    ecx, [esp + 16]

    xor    eax, eax
outsw_startLoop:
    cmp     ecx, eax
    je      outsw_end

    outsw

    inc    eax
    jmp     outsw_startLoop

outsw_end:
    pop    esi
    ret

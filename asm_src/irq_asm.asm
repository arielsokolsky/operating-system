
[bits 32]
section .text

%macro irq 2
global irq%1
irq%1: 
    cli
    push 0
    push %2
    jmp irq_stub
%endmacro

irq 0, 32
irq 1, 33
irq 2, 34
irq 3, 35
irq 4, 36
irq 5, 37
irq 6, 38
irq 7, 39
irq 8, 40
irq 9, 41
irq 10, 42
irq 11, 43
irq 12, 44
irq 13, 45
irq 14, 46
irq 15, 47


extern irq_handler
irq_stub:
    pusha

    mov	    ax, ds
    push	eax
    mov 	esi, eax

    ;change to kernel register
    mov     ax, 0x10
    mov 	ds, ax
    mov 	es, ax
    mov 	fs, ax
    mov 	gs, ax

    call irq_handler

    pop	    ebx
    mov 	ebx, esi

    mov 	ds, bx
    mov 	es, bx
    mov 	fs, bx
    mov 	gs, bx

    popa
    ;clean stack
    add esp, 8
    sti
    ret




bits 32

section .multiboot
        align   4
        dd      0x1BADB002 ;magic number
        dd      0x00 ;flags
        dd      - (0x1BADB002+0x00) ;checksum


section .text
extern main ;main function in kernel.c
global start ;entery point
start:
    cli ;disalbe interrupt
    mov esp, stack_end
    push ebx
    call main
    hlt;stop


section .bss
stack_start:
	resb 8*1024
stack_end:

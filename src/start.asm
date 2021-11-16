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
    call main
    hlt;stop




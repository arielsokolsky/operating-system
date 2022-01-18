#include "../include/tss.h"
#include "../include/gdt.h"
tss_t system_tss;


/*
the function the the stack
stack: the address of the stack
return: none
*/
void tssSetStack(uint32 stackPointer, uint32 stackSegment)
{
    system_tss.ss0 = stackSegment;
    system_tss.esp0 = stackPointer;
}


void tss_install(uint32 index, uint16 ss, uint16 esp)
{
    uint32 tss_addr = (uint32)&system_tss;
    uint32 size = tss_addr + sizeof(tss_t);

    set_gdt_gate(index, tss_addr, size, 0xE9, 0);

    memset(&system_tss, 0, sizeof(system_tss));

    system_tss.ss0 = ss;
    system_tss.esp0 = esp;
    system_tss.cs = 0x0B;
    system_tss.ds = 0x13;
    system_tss.es = 0x13;
    system_tss.fs = 0x13;
    system_tss.gs = 0x13;
    system_tss.ss = 0x13;
}


#include "../include/tss.h"
#include "../include/gdt.h"
tss_t system_tss;


/*
the function the the stack
stack: the address of the stack
return: none
*/
void tssSetStack(uint32 stack)
{
    system_tss.stack_segment0.esp = stack;
}


void tss_install(uint32 index, uint16 ss, uint16 esp)
{
    uint32 tss_addr = (uint32)&system_tss;
    uint32 size = tss_addr + sizeof(tss_t);

    set_gdt_gate(index, tss_addr, size, 0xE9, 0);

    system_tss.stack_segment0.ss = ss;
    system_tss.stack_segment0.esp = esp;

    system_tss.segment_registers.cs = 0x0B;
    system_tss.segment_registers.ds = 0x13;
    system_tss.segment_registers.es = 0x13;
    system_tss.segment_registers.fs = 0x13;
    system_tss.segment_registers.gs = 0x13;
    system_tss.segment_registers.ss = 0x13;

    tss_flush();
}


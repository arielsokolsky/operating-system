#include "../include/idt.h"



void changeIdtEntry(int num, unsigned_int32 handler) 
{
    idt[num].offestLow = low_16(handler);
    idt[num].selector = KERNEL_CS;
    idt[num].zero = 0;
    idt[num].flags = 0x8E;
    idt[num].offestTop = high_16(handler);
}

void setupIdt()
{
    _lidt.base = (unsigned_int32) &idt;
    _lidt.limit = NUM_OF_IDT_ENTRIES * sizeof(idtEntery) - 1;

    install_idt_entries();
    
    idt_load();
    print("idt is setup\n");
}


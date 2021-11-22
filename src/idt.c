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
    _lidt.limit = NUM_OF_IDT_NETRIES * sizeof(idtEntery) - 1;
    for (int i = 0; i < NUM_OF_IDT_NETRIES; i++)
    {
        changeIdtEntry(i, defult_handler);
    }
    
    idt_load();
}


void defult_handler()
{
    print("work");
    asm("hlt");
}

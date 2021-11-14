#include "../include/idt.h"

void setupIdt()
{
    _lidt.base = &idt;
    _lidt.limit = (sizeof(idtEntery) * NUM_OF_IDT_NETRIES) - 1;

    for (int i = 0; i < NUM_OF_IDT_NETRIES; i++)
    {
        changeIdtEntry(i, defult_handler, 0x71);
    }
    installIdt();
}


void changeIdtEntry(int num, unsigned_int32 address, unsigned_int8 flags)
{
    idt[num].zero = 0;
    idt[num].flags = flags;
    idt[num].selector = KERNEL_CS;
    idt[num].offestTop = (unsigned_int16)address >> 16;
    idt[num].offestLow = (unsigned_int16)address << 16;

}

void defult_handler()
{

}
#include "../include/isr.h"
#include "../include/screen.h"

void isr0()
{
    print(exception_messages[0]);
    asm("hlt");    
}
void isr1()
{
    print(exception_messages[1]);    
    asm("hlt");
}
void isr2()
{
    print(exception_messages[2]);    
    asm("hlt");
}
void isr3()
{
    print(exception_messages[3]);    
    asm("hlt");
}
void isr4()
{
    print(exception_messages[4]);    
    asm("hlt");
}
void isr5()
{
    print(exception_messages[5]);    
    asm("hlt");
}
void isr6()
{
    print(exception_messages[6]);    
    asm("hlt");
}
void isr7()
{
    print(exception_messages[7]);    
    asm("hlt");
}
void isr8()
{
    print(exception_messages[8]);    
    asm("hlt");
}
void isr9()
{
    print(exception_messages[9]);    
    asm("hlt");
}
void isr10()
{
    print(exception_messages[10]);    
    asm("hlt");
}
void isr11()
{
    print(exception_messages[11]);    
    asm("hlt");
}
void isr12()
{
    print(exception_messages[12]);    
    asm("hlt");
}
void isr13()
{
    print(exception_messages[13]);    
    asm("hlt");
}
void isr14()
{
    print(exception_messages[14]);    
    asm("hlt");
}
void isr15()
{
    print(exception_messages[15]);    
    asm("hlt");
}
void isr16()
{
    print(exception_messages[16]);    
    asm("hlt");
}
void isr17()
{
    print(exception_messages[17]);    
    asm("hlt");
}
void isr18()
{
    print(exception_messages[18]);    
    asm("hlt");
}
void isr19()
{
    print(exception_messages[19]);    
    asm("hlt");
}

void install_idt_entries()
{
    //set software interrupt entries
    println("software interrupt is setup");
    
    changeIdtEntry(0, isr0);
    changeIdtEntry(1, isr1);
    changeIdtEntry(2, isr2);
    changeIdtEntry(3, isr3);
    changeIdtEntry(4, isr4);
    changeIdtEntry(5, isr5);
    changeIdtEntry(6, isr6);
    changeIdtEntry(7, isr7);
    changeIdtEntry(8, isr8);
    changeIdtEntry(9, isr9);
    changeIdtEntry(10, isr10);
    changeIdtEntry(11, isr11);
    changeIdtEntry(12, isr12);
    changeIdtEntry(13, isr13);
    changeIdtEntry(14, isr14);
    changeIdtEntry(15, isr15);
    changeIdtEntry(16, isr16);
    changeIdtEntry(17, isr17);
    changeIdtEntry(18, isr18);
    changeIdtEntry(19, isr19);
}
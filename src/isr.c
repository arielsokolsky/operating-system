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


string exception_messages[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
};

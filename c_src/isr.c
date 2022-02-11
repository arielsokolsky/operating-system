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

void irq0()
{
    print(irq_messages[0]);  
}

void irq1()
{
    print(irq_messages[1]);
    asm("hlt");
}

void irq2()
{
    print(irq_messages[2]);
}

void irq3()
{
    print(irq_messages[3]);
}

void irq4()
{
    print(irq_messages[4]);
}

void irq5()
{
    print(irq_messages[5]);
}

void irq6()
{
    print(irq_messages[6]);
}   

void irq7()
{
    print(irq_messages[7]);
}

void irq8()
{
    print(irq_messages[8]);
}

void irq9()
{
    print(irq_messages[9]);
}

void irq10()
{
    print(irq_messages[10]);
}

void irq11()
{
    print(irq_messages[11]);
}

void irq12()
{
    print(irq_messages[12]);
}

void irq13()
{
    print(irq_messages[13]);
}

void irq14()
{
    print(irq_messages[14]);
}

void irq15()
{
    print(irq_messages[15]);
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

    //set irq entries
    println("irq is setup");

    changeIdtEntry(32, irq0);
	changeIdtEntry(33, irq1);
	changeIdtEntry(34, irq2);
	changeIdtEntry(35, irq3);
	changeIdtEntry(36, irq4);
	changeIdtEntry(37, irq5);
	changeIdtEntry(38, irq6);
	changeIdtEntry(39, irq7);
	changeIdtEntry(40, irq8);
	changeIdtEntry(41, irq9);
	changeIdtEntry(42, irq10);
	changeIdtEntry(43, irq11);
	changeIdtEntry(44, irq12);
	changeIdtEntry(45, irq13);
	changeIdtEntry(46, irq14);
	changeIdtEntry(47, irq15);


}
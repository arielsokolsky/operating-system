#include "../include/irq.h"

static string irq_messages[NUM_OF_IRQ] =
{
    "Programmable Interrupt Timer Interrupt", \
 	"Keyboard Interrupt", \
 	"Cascade used internally by the two PICs", \
 	"COM2 enabled", \
 	"COM1", \
 	"LPT2", \
 	"Floppy Disk", \
 	"LPT1 / Unreliable interrupt", \
 	"CMOS real-time clock ", \
 	"Free for peripherals / legacy SCSI / NIC", \
 	"Free for peripherals / SCSI / NIC", \
 	"Free for peripherals / SCSI / NIC", \
 	"PS2 Mouse", \
 	"FPU / Coprocessor / Inter-processor", \
 	"Primary ATA Hard Disk", \
 	"Secondary ATA Hard Disk "
};

/*
the function install the irq
param: none
return: none
*/
void installIrq()
{
    remapIrq();
    
	//add the irq to the idt
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

    println("irq is setup");
}

/*
the function
param: none
return: none
*/
void setIrqEnery(int num, void *handler)
{
	irq_handlers[num] = handler;
}

/*
the function handle the irq interrupt
param: all the register (interrupt number, etc...)
return: none
*/
void irq_handler(registers_t regs)
{
	//pointer to the function
	void (*handler)(struct registers_t* regs);
	int entry = regs.int_no - 32;

	handler = irq_handlers[entry];

	//if function exists and not timer interrupt
	if(handler && entry != 0)
	{
		handler(&regs);
	}

	//If index greater than 40, we must reset the slave 
    if(regs.int_no >= 40)
    {
        //reset slave
        outPort(SLAVE_COMMAND, PIC_RESET);
    }

    outPort(MASTER_COMMAND, PIC_RESET);

	//we can only use the timer interrupt after the EOI
	if (handler && regs.int_no - 32 == 0)
	{
		handler(&regs);
	}
}

void keyboard_handler()
{
	int byte = inputPort(0x60);
}
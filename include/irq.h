#ifndef IRQ_h
#define IRQ_H

#include "system.h"
#include "string.h"
#include "screen.h"

#define NUM_OF_IRQ 16

void installIrq();


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

#endif
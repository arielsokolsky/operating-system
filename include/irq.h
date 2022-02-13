#ifndef IRQ_h
#define IRQ_H

#include "system.h"
#include "string.h"
#include "screen.h"
#include "pic.h"

#define NUM_OF_IRQ 16

void* irq_handlers[NUM_OF_IRQ];

void setIrqEnery(int num, void* handler);
void installIrq();
void irqRemape();
void irq_handler(registers_t);

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();


void keyboard_handler();



#endif
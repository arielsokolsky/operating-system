#ifndef IDT_H
#define IDT_H

#define KERNEL_CS 0x08
#define NUM_OF_IDT_NETRIES 256

#include "types.h"

/*
base - point to the start of the idt
limit - the length of the table(to find the end of table)
*/
typedef struct idtPointer
{
    int base;
    int limit;
}idtPointer;

/*
offestTop - the first part of the address
selector - the kernel code segmenet
zero - a zero
flags - how the flags work:
0-5 bits: always 01110
6-7 bits: ring
8 bit: if segment present 
offestLow - the second part of the address
*/
typedef struct idtEntery
{
    unsigned_int16 offestTop;
    unsigned_int16 selector;
    unsigned_int8 zero;
    unsigned_int8 flags;
    unsigned_int16 offestLow;
}idtEntery;

idtEntery idt[NUM_OF_IDT_NETRIES];
idtPointer _lidt;

//the function setupt the idtPionter and clear entries
void setupIdt();
//the function tell the processer where the table8o
extern void installIdt();
//the function change entery
void changeIdtEntry(int num, unsigned_int32 address, unsigned_int8 flags);
//the defult isr
void defult_handler();

#endif
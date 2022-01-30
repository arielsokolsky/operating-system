#ifndef IDT_H
#define IDT_H

#include "types.h"
#include "screen.h"
#define KERNEL_CS 0x08
#define NUM_OF_IDT_ENTRIES 256

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
    unsigned_int16 offestLow;
    unsigned_int16 selector;
    unsigned_int8 zero;
    unsigned_int8 flags;
    unsigned_int16 offestTop;
} __attribute__((packed)) idtEntery;

/*
base - point to the start of the idt
limit - the length of the table(to find the end of table)
*/
typedef struct idtPointer
{
    unsigned_int16 limit;
    unsigned_int32 base;
} __attribute__((packed)) idtPointer;


static idtEntery idt[NUM_OF_IDT_ENTRIES];
idtPointer _lidt;

//the function setupt the idtPionter and clear entries
void setupIdt();
//the function tell the processer where the table
extern void idt_load();
//the function change entery
void changeIdtEntry(int num, unsigned_int32 address);

#endif
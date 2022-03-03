#ifndef SYSTEM_H
#define SYSTEM_H
#include "types.h"

uint8 inputPort(uint16 port);
uint16 inputPortWord(uint16 port);
uint32 inputPortDword(uint16 port);

void outPort(uint16 port, uint8 data);
void outPortWord(uint16 port, uint16 data);
void outPortDword(uint16 port, uint32 data);

extern void insw(uint16 port, void *addr, unsigned int count);
extern void outsw(uint16 port, void *addr, unsigned int count);

typedef struct registers
{
    uint32 ds;// Data segment selector
    uint32 edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha.
    uint32 int_no, err_code;// Interrupt number and error code (if applicable)
    uint32 eip, cs, eflags, useresp, ss;// Pushed by the processor automatically.
} __attribute__((packed)) registers_t;

#endif
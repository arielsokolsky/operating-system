#ifndef SYSTEM_H
#define SYSTEM_H
#include "types.h"

unsigned_int8 inputPort(unsigned_int16 port);
void outPort(uint16 port, unsigned_int8 data);


typedef struct registers
{
    uint32 ds;// Data segment selector
    uint32 edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha.
    uint32 int_no, err_code;// Interrupt number and error code (if applicable)
    uint32 eip, cs, eflags, useresp, ss;// Pushed by the processor automatically.
} __attribute__((packed)) registers_t;

#endif
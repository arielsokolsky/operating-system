#ifndef SYSTEM_H
#define SYSTEM_H
#include "types.h"

unsigned_int8 inputPort(unsigned_int16 port);
void outportb (uint16 port, uint8 data);
extern void insw(uint16 port, void *addr, unsigned int count);
extern void outsw(uint16 port, void *addr, unsigned int count);

#endif
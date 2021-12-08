#ifndef MALLOC_H
#define MALLOC_H

#include "types.h"


bool enable = true;
extern uint32 end_of_kernel;
//start allocating from the end of the kernel
uint32 currentAddress = &end_of_kernel;

uint32 malloc (uint32 size, uint32* phys);


#endif
#ifndef MALLOC_H
#define MALLOC_H

//#include "types.h"
#include "multi_boot.h"
#include "screen.h"

#define PAGE_SIZE 0x1000 

static bool enable = true;
extern uint32 end_of_kernel;
//start allocating from the end of the kernel
static uint32 currentAddress = &end_of_kernel;

uint32 mallocBasic (uint32 size, bool aligened, uint32* phys);
uint32 stopMalloc();

#endif
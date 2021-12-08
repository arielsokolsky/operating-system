#include "../include/malloc.h"

/*
the function allocate memory
size: how many byte to allocate
phys: a pointer the to the start of the allocated section
ret: the end of the allocated section
*/
uint32 malloc(uint32 size, uint32 *phys)
{
    //check that malloc isn't stopped (to prevent memory leak)
    if(!enable)
    {
        return 0;
    }

    //set physical to the start
    *phys = currentAddress;
    currentAddress += size;
    return currentAddress;
}

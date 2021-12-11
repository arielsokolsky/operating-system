#include "../include/malloc.h"

/*
the function allocate memory
size: how many byte to allocate
phys: a pointer the to the start of the allocated section
ret: the end of the allocated section
*/
uint32 mallocBasic(uint32 size, bool aligened, uint32 *phys)
{
    uint32 temp;
    //check that malloc is enabled
    if(!enable)
    {
        print("error: malloc is enabled");
        asm("hlt");
    }

    //if aligend start from the start of page
    if (aligened && (currentAddress & 0xFFFFF000))
    {
        //removing the offest
        currentAddress &= 0xFFFFF000;
        currentAddress += PAGE_SIZE;
    }
    //get the pointer
    if (phys)
    {
        *phys = currentAddress;
    }

    temp = currentAddress;
    temp += size;

    return currentAddress;
}


/*
the function is disalbing malloc after allocating in order to not leak memory
return: the last address 
*/
uint32 stopMalloc()
{
    uint32 end = currentAddress;

    //check if start of page(offest)
    if(!(end & 0xFFF))
    {
        return end;
    }
    //move to the next page and disable paging (in order not to leak memory)
    end &= 0xFFFFF000;
    end += PAGE_SIZE;
    enable = false;
    return end;

}



#include "../include/tss.h"
tss_t myTss;


/*
the function the the stack
stack: the address of the stack
return: none
*/
void tssSetStack(uint32 stack)
{
    myTss.stack_segment0.esp = stack;
}



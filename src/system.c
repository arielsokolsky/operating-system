#include "../include/system.h"



unsigned_int8 inputPort(unsigned_int16 port)
{
    unsigned_int8 recived_input;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (recived_input) : "dN" (port));
    return recived_input;
}


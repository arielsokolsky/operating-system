#include "../include/system.h"


/*
the function get a input from a port (in this case used to get irq when keyboard press)
param: the port to read from
return: the message (buffer)
*/
unsigned_int8 inputPort(unsigned_int16 port)
{
    unsigned_int8 recived_input;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (recived_input) : "dN" (port));
    return recived_input;
}


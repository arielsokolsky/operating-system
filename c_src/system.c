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

/*
the function let us write to ports data
param port: the port to write to
param data: the data we want to write to that port
return: none
*/
void outPort(uint16 port, unsigned_int8 data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (port), "a" (data));
}



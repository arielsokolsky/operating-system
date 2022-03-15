#include "../include/system.h"


/*
the function get a input from a port 
param: the port to read from
return: the message (buffer)
*/
uint8 inputPort(uint16 port)
{
    uint8 input;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (input) : "dN" (port));
    return input;
}


//the same as inputPort but we get 2 byte
uint16 inputPortWord(uint16 port)
{
    uint16 input;
    __asm__("in %%dx, %%ax" : "=a" (input) : "d" (port));
    return input;
}

//the same as inputPort but we get 4 byte
uint32 inputPortDword(uint16 port)
{
    uint32 input;
    __asm__("in %%dx, %%eax" : "=a" (input) : "d" (port));
    return input;
}


/*
the function let us write to ports data
param port: the port to write to
param data: the data we want to write to that port
return: none
*/
void outPort(uint16 port, uint8 data)
{
	__asm__ __volatile__ ("outb %1, %0" : : "dN" (port), "a" (data));
}


//the same as outPort but we write 2 byte
void outPortWord(uint16 port, uint16 data)
{
    __asm__("out %%ax, %%dx" : : "a" (data), "d" (port));
}

//the same as outPort but we write 4 byte
void outPortDword(uint16 port, uint32 data)
{
    __asm__("out %%eax, %%dx" : : "a" (data),  "d" (port));
}



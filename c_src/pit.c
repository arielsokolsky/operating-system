#include "../include/pit.h"


void timerHandler()
{
}

void init_timer(uint32 frequency)
{
    setIrqEnery(0, timerHandler);
    irq0();
}




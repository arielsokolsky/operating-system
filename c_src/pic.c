#include "../include/pic.h"


/*
the function remape the irq (because the defulat locatin of irq as the same as software interrupt)
param: none
return: none
*/
void remapIrq()
{
    outPort(MASTER_COMMAND, ICW1_INIT | ICW1_ICW4); // Start initialization sequence
    outPort(SLAVE_COMMAND, ICW1_INIT | ICW1_ICW4);  // Start initialization sequence
    outPort(MASTER_DATA, 0x20);                     // Remap to 0x20
    outPort(SLAVE_DATA, 0x28);                      // Remap slave to 0x28
    outPort(MASTER_DATA, 4);                        // Tell Master about slave @ IRQ 2
    outPort(SLAVE_DATA, 2);                         // Tell slave PIC its cascade ID

    outPort(MASTER_DATA, ICW4_8086);
    outPort(SLAVE_DATA, ICW4_8086);

    outPort(MASTER_DATA, 0x0);
    outPort(SLAVE_DATA, 0x0);
    println("remape");
}




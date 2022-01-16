#include "../include/gdt.h"
#include "../include/tss.h"


//set a specific entry in the gdt table
void set_gdt_gate(unsigned_int8 entry, unsigned_int32 base, unsigned_int32 limit, unsigned_int8 access, unsigned_int8 flags)
{
    gdt[entry].low_base = (base & 0xFFFF);
    gdt[entry].middle_base = (base >> 16) & 0xFF;
    gdt[entry].high_base = (base >> 24) & 0xFF;

    gdt[entry].low_limit = (limit & 0xFFFF); 
    gdt[entry].limit_and_flags = (limit >> 16) & 0x0F;  //gdt[entry_num].limit_and_flags = ((limit >> 16) & 0x0F) + (flags & 0xF0);

    gdt[entry].limit_and_flags |= flags & 0xF0;
    gdt[entry].access_byte = access;
}

//creates the gdt table and its pointer, and sets up the
//first 3 segments in the gdt table
//and then flushes the segments
void install_gdt()
{
    gp.limit = (sizeof(struct gdt_entry) * 5) - 1;
    gp.base = (unsigned_int32) &gdt;

    set_gdt_gate(0, 0 ,0, 0, 0);
    //code segment
    set_gdt_gate(1 ,0 , 0xFFFFFFFF, 0x9A, 0xCF);
    //data segment
    set_gdt_gate(2 ,0 , 0xFFFFFFFF, 0x92, 0xCF);
    //User mode code segment
    set_gdt_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); 
    //User mode data segment
    set_gdt_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); 

    tss_install(5, 0x10, 0);

    _gdt_flush();
    tss_flush();
    print("gdt is setup\n");
}
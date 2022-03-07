#ifndef GDT_H
#define GDT_H
#include "types.h"
#define NUM_DESCRIPTORS 8
//the entry struct in the gdt table
//the struct is packed so the complier will won't try to "optimize" the struct in the memory
typedef struct gdt_entry{
    uint16 low_limit;
    uint16 low_base;
    uint8 middle_base;
    uint8 access_byte;
    uint8 limit_and_flags;
    uint8 high_base;
} __attribute__((packed)) gdt_entry;



//the poiter for the gdt table
typedef struct gdt_ptr {
    uint16 limit;
    uint32 base;
}__attribute__((packed)) gdt_ptr;

gdt_entry gdt[NUM_DESCRIPTORS];
gdt_ptr gp;

//this function is in the start.asm file
//the function will reload the new segment register
extern void _gdt_flush();

void set_gdt_gate(uint8 entry_num, uint32 base, uint32 limit, uint8 access, uint8 flags);
void install_gdt();

#endif
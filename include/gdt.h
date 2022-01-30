#ifndef GDT_H
#define GDT_H
#include "types.h"
#define NUM_DESCRIPTORS 8
//the entry struct in the gdt table
//the struct is packed so the complier will won't try to "optimize" the struct in the memory
typedef struct gdt_entry{
    unsigned_int16 low_limit;
    unsigned_int16 low_base;
    unsigned_int8 middle_base;
    unsigned_int8 access_byte;
    unsigned_int8 limit_and_flags;
    unsigned_int8 high_base;
} __attribute__((packed)) gdt_entry;



//the poiter for the gdt table
typedef struct gdt_ptr {
    unsigned_int16 limit;
    unsigned_int32 base;
}__attribute__((packed)) gdt_ptr;

gdt_entry gdt[NUM_DESCRIPTORS];
gdt_ptr gp;

//this function is in the start.asm file
//the function will reload the new segment register
extern void _gdt_flush();

void set_gdt_gate(unsigned_int8 entry_num, unsigned_int32 base, unsigned_int32 limit, unsigned_int8 access, unsigned_int8 flags);
void install_gdt();

#endif
#ifndef TSS_H
#define TSS_H
#include "types.h";

extern void flush_tss();

void tssSetStack(uint32 stack);
void tssInit(uint32 num, uint16 ss0, uint16 esp0);
void tssSwitch();

typedef struct stack_segment
{
    uint32 esp;
    uint16 ss;
    uint16 ss_h;
} __attribute__((packed)) stack_segment_t;

typedef struct stack_registers
{
    uint32 esp; //stack pointer
    uint32 ebp; //base pointer
}__attribute((packed)) stack_registers_t;



typedef struct pointer_registers
{
    uint32 esi; //source index
    uint32 edi; //destination index
}__attribute((packed)) pointer_registers_t;


typedef struct execution_state
{
    uint32 eip; 
    uint32 eflags;
}__attribute((packed)) execution_state_t;



typedef struct segment_registers
{
    uint16 es; //extra segment
    uint16 es_h;

    uint16 cs; //code segment
    uint16 cs_h;

    uint16 ss; //stack segment
    uint16 ss_h;

    uint16 ds; //data segment
    uint16 ds_h;

    uint16 fs; // extra segment(newer)
    uint16 fs_h;
    
    uint16 gs; //extra segment(newer)
    uint16 gs_h;
}__attribute__((packed)) segment_registers_t;



typedef struct general_purpose_registers
{
    uint32 eax; //accumlator
    uint32 ecx; //counter
    uint32 edx; //data
    uint32 ebx; //base 
}__attribute__((packed)) general_purpose_registers_t;



typedef struct tss
{
    //check if called by `CALL` or `INT` or rather by `JMP`
    uint16 link;
    uint16 link_h;
    
    //stack pointer(esp) and stack segment(ss)
    stack_segment_t stack_segment0;
    stack_segment_t stack_segment1;
    stack_segment_t stack_segment2;

    //control register3 - point to Page Directory Base Register (PDBR)
    uint32 cr3; 
    
    //execution_state
    execution_state_t execution_state;

    //general purpose registers
    general_purpose_registers_t general_purpose_registers;

    //stack registers
    stack_registers_t stack_registers;    

    //pointer_registers
    pointer_registers_t pointer_registers;

    //segment registers
    segment_registers_t segment_registers;

    //pointer to the ldt local descriptor table
    uint16 ldtr; 
    uint16 ldtr_h;

    uint16 trap;
    uint16 iomap;
} __attribute__((packed)) tss_t;


#endif
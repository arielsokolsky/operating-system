#ifndef TASK_H
#define TASK_H

#define STACK_SIZE 8*1024

#include "types.h"
#include "paging.h"
#include "frame.h"

typedef struct task
{
    int id;
    uint32 esp;
    uint32 ebp;
    uint32 eip;
    page_directory *page_dir;
    uint32 kernel_stack;
    struct task_t* next;
}task_t;

task_t* ready_queue;
task_t* current_task;

extern uint32 stack_end;

extern uint32 read_eip();
extern void flush_tlb();
void move_stack(void* new_stack_start, uint32 size);
uint32 getpid();
void task_install();
void task_switch();

#endif
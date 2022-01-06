#ifndef TASK_H
#define TASK_H

#include "types.h"
#include "paging.h"

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

extern void to_esp(uint32 esp);

//void task_install();
//void task_switch();
//void move_stack(void* new_stack_start, uint32 size);

uint32 getpid();

#endif
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
    task_t* next;
}task_t;


#endif
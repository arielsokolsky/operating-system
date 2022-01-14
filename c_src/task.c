#include "../include/task.h"
int next_pid = 1;

uint32 getpid()
{
    return current_task->id;
}

/*
the function allocate a new stack and copy to old one into it
param: new_stack_start: the new stack start
param: size: the size of the stack
return: none
*/
void move_stack(void* new_stack_start, uint32 size)
{  
    string str = "12345";
    uint32 newStackPointer = 0, oldStackPointer = 0, newStackBase = 0, oldStackBase = 0;
    
    //allocate the stack
    for (uint32 i = (uint32)new_stack_start; i < (uint32)new_stack_start - size; i -= PAGE_SIZE)
    {
        allocateFrame(get_page(i, 1, current_directory), 1, 0);
    }

    flush_tlb();

    //get the old stack and base pointer
    asm volatile ("mov %%esp, %0" : "=r" (oldStackPointer));
    asm volatile ("mov %%ebp, %0" : "=r" (oldStackBase));
    println("flush tlb");



}


/*
the function setup a task mechanism
return: none
*/
void task_install()
{
    move_stack((void*)(0xE0000000), PAGE_SIZE);
    println("move stack\n");
    
    task_t myTask;

    myTask.id = 1;
    myTask.eip = 0;
    myTask.ebp = 0;
    myTask.esp = 0; 
    myTask.page_dir = current_directory;
    myTask.next = 0;
    myTask.kernel_stack = malloc_a(KERNEL_STACK_SIZE);

    next_pid += 1;
    current_task = &myTask;
    ready_queue = current_task;

}



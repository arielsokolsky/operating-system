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
    uint32 newStackPointer = 0, oldStackPointer = 0;
    uint32 newStackBase = 0, oldStackBase = 0;
    uint32 offset = 0;
    
    //allocate the stack
    for (uint32 i = (uint32)new_stack_start; i < (uint32)new_stack_start - size; i -= PAGE_SIZE)
    {
        allocateFrame(get_page(i, 1, current_directory), 1, 0);
    }

    flush_tlb();
    println("flush tlb");

    //get the old stack and base pointer
    asm volatile ("mov %%esp, %0" : "=r" (oldStackPointer));
    asm volatile ("mov %%ebp, %0" : "=r" (oldStackBase));
    
    offset = (uint32)new_stack_start - stack_end;

    newStackBase = oldStackBase + offset;
    newStackPointer = oldStackPointer + offset;
    printInt(newStackPointer);
    printInt(oldStackPointer);
    //copy the stack
    memcpy((void*)newStackPointer, (void*)oldStackPointer, stack_end - oldStackPointer);
    
    //set esp and ebp
    asm volatile("mov %0, %%esp" : : "r" (newStackPointer));
	asm volatile("mov %0, %%ebp" : : "r" (newStackBase));

}


/*
the function setup a task mechanism
return: none
*/
void task_install()
{
    move_stack((void*)(0xE0000000), STACK_SIZE);
    println("move stack\n");
    
    task_t myTask;

    myTask.id = 1;
    myTask.eip = 0;
    myTask.ebp = 0;
    myTask.esp = 0; 
    myTask.page_dir = current_directory;
    myTask.next = 0;
    myTask.kernel_stack = malloc_a(STACK_SIZE);

    next_pid += 1;
    current_task = &myTask;
    ready_queue = current_task;

}

/*
the function switch to the next task
param: none
return: none
*/
void task_switch()
{
    uint32 ebp = 0, esp = 0, eip = 0;
    //check that task initiailzed
    if(!current_task)
    {
        return;
    }

    //get registers values
    asm volatile ("mov %%esp, %0" : "=r" (esp));
    asm volatile ("mov %%ebp, %0" : "=r" (ebp));
    eip = get_eip();

    //if equal to dummy value that mean we switched
    if(eip == 0x12345)
        return;

    //go the next task
    current_task = current_task->next;
    //if doesn't exist fetch from ready queue
    if(!current_task)
    {
        current_task = ready_queue;
    }

    esp = current_task->esp;
    ebp = current_task->ebp;
    eip = current_task->eip;

    current_directory = current_task->page_dir;
    //tss set kernel stack

    asm volatile("				\
        ;disable interrupt      \
        cli;                    \
        ;save eip in ecx		\
    	mov %0, %%ecx           \
        ;load new stack			\
    	mov %0, %%esp			\
        mov %0, %%ebp			\
        ;load new page ditroctry\
        mov %0, %%cr3           \
        ;put dummy value in eax \
        mov 0x12345, eax        \
        ;enable interrupt       \
        sti                     \
    	jmp *%%ecx"                             
        : : "r"(eip) "r"(esp) "r"(ebp) "r"(current_directory));

    
}




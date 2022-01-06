#include "../include/task.h"
unsigned int next_pid = 1;

uint32 getpid()
{
    return current_task->id;
}
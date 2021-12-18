#include "../include/frame.h"


unsigned_int32 stack_count = 0;
unsigned_int32* free_frames = 0;
int32 top_of_stack = -1;

unsigned_int32 end_of_memory = 0;
unsigned_int32 allocated_frames = 0;
unsigned_int32 total_frames;


void intialize_frame_allocator(uint32 system_frames)
{
    //changes the amount of total frame to the amount that the boot loader gave
    total_frames = system_frames;
    //if the free_frame wasn't alloctated before, the it will 
    //allocate the pointer in the memory for the right amount of frames
    if (free_frames == 0)
    {
        free_frames = (uint32*) malloc(system_frames * sizeof(uint32));
        stack_count = system_frames;
    }
}
void free_frame(struct page *page)
{
    //increases the last slot in free frames to an empty one
    top_of_stack++;

    //puts the frameAddress in the top of free_frames so it could be used later
    free_frames[top_of_stack] = page->frameAddress;
    page->frameAddress = 0;
    allocated_frames--;
}
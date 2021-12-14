#include "../include/frame.h"


unsigned_int32 stack_count = 0;
unsigned_int32* free_frames = 0;
int32 top_of_stack = -1;

unsigned_int32 end_of_memory = 0;
unsigned_int32 allocated_frames = 0;
unsigned_int32 total_frames;
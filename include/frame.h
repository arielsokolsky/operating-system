#ifndef FRAME_H
#define FRAME_H
#include "paging.h"

void intialize_frame_allocator(uint32 system_frames);
void free_frame(struct page *page);


#endif
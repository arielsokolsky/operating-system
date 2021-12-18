#ifndef FRAME_H
#define FRAME_H
#include "paging.h"
#include "malloc.h"
#include "screen.h"

void initFrameAllocator(int NumOfFrames);
uint32 allocateFrame(page* myPage, bool isWritable, bool isKernel);
page* getPage(uint32 frameAddress);

#endif
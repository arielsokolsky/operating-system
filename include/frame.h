#ifndef FRAME_H
#define FRAME_H
#include "paging.h"
#include "screen.h"

void initFrameAllocator(int NumOfFrames);
void allocateFrame(page* myPage, bool isWritable, bool isKernel);
void freeFrame(page* myPage);

#endif

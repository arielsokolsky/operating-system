#include "../include/frame.h"


//array that contains the frames is used
unsigned_int32* freeFrames = 0;
unsigned_int32 numOfAllocatedFrames = 0;
unsigned_int32 numOfFrames = 0;



/*
the function initialize the frames
param _numOfFrames: the number of frames
return: none
*/
void initFrameAllocator(int _numOfFrames)
{
    //if already allocated exit function
    if(freeFrames)
    {
        print("error: already allocated");
        return;
    }
    numOfFrames = _numOfFrames; 
    freeFrames = (uint32* )malloc(sizeof(uint32) * numOfFrames);
}

/*
the function allocate a frame
param myPage: the page that we want to allocate
param isWritable: if the page is writable
param isKernel: if the page is kernel page
return: the frame number
*/
uint32 allocateFrame(page* myPage, bool isWritable, bool isKernel)
{
    //check if already allocated
    if(freeFrames[myPage->frameAddress] != 0)
    {
        print("error: frame already allocated\n");
        return;
    }

    //check that there is a free frame
    if(numOfAllocatedFrames == numOfFrames)
    {
        print("error: cannot allocate more frames\n");
        return;
    }
    
    //set frame as occupied
    freeFrames[myPage->frameAddress] = 1;

    //set the page
    myPage->present = 1;
    myPage->user = isKernel ? 0 : 1;
    myPage->readwrite = isWritable ? 1 : 0;
    myPage->frameAddress = numOfAllocatedFrames;

    numOfAllocatedFrames++;
    return numOfAllocatedFrames - 1;
}

/*
the function free a frame
param myPage: the page that we want to free
return: none
*/
void freeFrame(page* myPage)
{
    uint32 index = myPage->frameAddress;

    //check if not allocated
    if(!freeFrames[index])
    {
        return;
    }

    //set frame as free
    freeFrames[index] = 0;

    numOfAllocatedFrames--;

    //set page as not present
    myPage->present = 0;
    myPage->user = 0;
    myPage->readwrite = 0;
    myPage->frameAddress = 0;
}



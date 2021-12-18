#include "../include/paging.h"

/*
the function sets up the paging in the memory
total_frames: gets the total amount of frames (using the bootloader)
ret: none
*/
void initialize_paging(unsigned_int32 total_frames) 
{

    current_directory = kernel_directory;
    
    // Go ahead and allocate all the page tables for the kernel.
    // This is wasteful, but a lot easier than figuring out how to build
    // a kernel page allocator.
    unsigned_int32 i = 0;
    _physicalAddr = &kernel_directory->physicalAddress;

    enablePaging();
    loadPageDirectory(_physicalAddr);

}

/*
the function gives tou the page using the address
address: the address of the page you want to get
dir: where the page table is in
ret: the page that the address belonged to
*/
page *get_page(unsigned_int32 address, page_directory *dir)
{
    // removes the files offset from the address by shifting the address using division of the necessery amount of bits
    address /= OFFSET_LEN;
    // Find the page table containing this address
    unsigned_int32 table_idx = address / ENTERY_SIZE;
    if (dir->tables[table_idx] != 0) // If this table is already assigned in the table
    {
        //returns the page in the correct table and page
        return &dir->tables[table_idx]->pages[address % ENTERY_SIZE];
    }
    else
    {
        return 0;
    }
}

/*
the function get a frame by his address
param freeAddress: the address of the frame
param myPage: the page that we want to get
return: the page
*/
page* getPageByFrame(uint32 frameAddress)
{
    return get_page(frameAddress , current_directory);
}


/*
the function map page
param: the address of the page we want to map
return: the allocated page
*/
page* mapPage(uint32 address)
{
    bool isKernel = current_directory->physicalAddress == kernel_directory->physicalAddress;
    page *myPage = getPageByFrame(address);
    if(myPage == 0)
    {
        print("error: page not found\n");
        return;
    }
    //allocate page
    allocateFrame(myPage, true, isKernel); 
    return myPage;
}



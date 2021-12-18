#include "../include/paging.h"


/*
the function sets up the paging in the memory
total_frames: gets the total amount of frames (using the bootloader)
ret: none
*/
void initialize_paging(unsigned_int32 total_frames) 
{

    intialize_frame_allocator(total_frames);

    kernel_directory = (struct page_directory *) malloc_a(sizeof(struct page_directory));
    memset(kernel_directory, 0, sizeof (struct page_directory));
    current_directory = kernel_directory;
    
    // Go ahead and allocate all the page tables for the kernel.
    // This is wasteful, but a lot easier than figuring out how to build
    // a kernel page allocator.
    unsigned_int32 i = 0;
    _physicalAddr = &kernel_directory->physicalAddress;

    switch_page_directory(_physicalAddr);

}


void switch_page_directory(struct page_directory * addr)
{
    loadPageDirectory(addr);
    enablePaging();
}
/*
the function gives tou the page using the address
address: the address of the page you want to get
dir: where the page table is in
ret: the page that the address belonged to
*/


page *get_page(unsigned_int32 address, bool make, struct page_directory *dir)
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
    else if (make)
    {
        return make_page(address, dir);

    }
    else if (make)
    {
        return make_page(address, dir);

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




struct page *make_page(unsigned_int32 address, struct page_directory *dir)
{
    uint32 newAddr;
    //allocate the page in the table
    dir->tables[address / 1024] = (struct page_table *)malloc_ap(sizeof(struct page_table), &newAddr);
    //memset the number of frames in table times the number of bits in frame address
    memset(dir->tables[address / 1024], 0, 1024 * 4 );
    dir->tablesPhysicalAdrs[address / 1024] = newAddr | 0x7;
    return &dir->tables[address / 1024]->pages[address%1024];
}

void clear_page(uint32 address)
{
    struct page *p = get_page(address, false, kernel_directory);
    if(p) {
        free_frame(p);
    }
}

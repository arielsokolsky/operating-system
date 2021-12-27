#include "../include/paging.h"


/*
the function sets up the paging in the memory
total_frames: gets the total amount of frames (using the bootloader)
ret: none
*/
void initialize_paging(unsigned_int32 total_frames) 
{
    uint32 _address = 0;
    uint32 i = 0;
    initFrameAllocator(total_frames);

    kernel_directory = (page_directory *) malloc_a(sizeof(page_directory));
    memset(kernel_directory, 0, sizeof (page_directory));
    current_directory = kernel_directory;
    
    // making the kernel pages
    for(i = 0; i < 0xFFFFFFFF;) 
    {
        get_page(i, 1, kernel_directory);
        i += 0x1000 * 1024;
        if(i == 0) {
            break;
        }
    }

    printInt(currentAddress);
    // allocating the kernel frames
    i = 0;
    while(i < currentAddress)
    {
        printInt(i);
        // Kernel code is readable but not writeable from userspace.
        allocateFrame( get_page(i, true, kernel_directory), 0, 0);
        i += 0x1000;
    }

    _physicalAddr = &kernel_directory->physicalAddress;
    print("working");
    switch_page_directory(_physicalAddr);
    initialized = true;

}


void switch_page_directory(page_directory * addr)
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


page *get_page(unsigned_int32 address, bool make, page_directory *dir)
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
    return get_page(frameAddress, false, current_directory);
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

page *make_page(unsigned_int32 address, page_directory *dir)
{
    uint32 newAddr;
    //allocate the page in the table
    dir->tables[address / ENTERY_SIZE] = (page_table *)malloc_ap(sizeof(page_table), &newAddr);
    //memset the number of frames in table times the number of bits in frame address
    memset(dir->tables[address / ENTERY_SIZE], 0, ENTERY_SIZE * 4 );
    dir->tablesPhysicalAdrs[address / ENTERY_SIZE] = newAddr | 0x7;
    return &dir->tables[address / ENTERY_SIZE]->pages[address % ENTERY_SIZE];
}

void clear_page(uint32 address)
{
    page *p = get_page(address, false, kernel_directory);
    if(p) {
        freeFrame(p);
    }
}

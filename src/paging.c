#include "../include/paging.h"
#include "../include/frame.h"
/*
the function sets up the paging in the memory
total_frames: gets the total amount of frames (using the bootloader)
ret: none
*/
void initialize_paging(unsigned_int32 total_frames) 
{
    page* myPage; 
    uint32 _address = 0;
    unsigned int i = 0;
    initFrameAllocator(total_frames);

    kernel_directory = (page_directory *) malloc_a(sizeof(page_directory));
    memset(kernel_directory, 0, sizeof(page_directory));
    kernel_directory->physicalAddress = (uint32)kernel_directory->tablesPhysicalAdrs;

    current_directory = kernel_directory;

    // allocate the page tables
    for(i = 0; i < 0xFFFFFFFF;) 
    {
        get_page(i, 1, kernel_directory);
        i += 0x1000 * 1024;
        if(i == 0) 
        {
            break;
        } 
    }

    // allocating the kernel frames
    i = 0;
    while(i < currentAddress)
    {
        myPage = get_page(i, 1, kernel_directory);    
        // Kernel code is readable but not writeable from userspace.
        allocateFrame(myPage, 0, 0);
        i += 0x1000;
    }
    
    _physicalAddr = &kernel_directory->physicalAddress;
    switch_page_directory(kernel_directory);

    initialized = true;
    print("initialize_paging");
    return;

}


void switch_page_directory(page_directory * directory)
{
    uint32* tablesPointer = &directory->tablesPhysicalAdrs;
    current_directory = directory;

    asm volatile("mov %0, %%cr3":: "r"(tablesPointer));
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

    if (dir->tables[table_idx] != 0) // If this table is already assigned
    {        
        //returns the page in the correct table and page
        return &dir->tables[table_idx]->pages[address % ENTERY_SIZE];
    }
    else if (make)
    {
        return make_page(address, dir);
    }
    else
    {
        print("error page table not exists :(\n");
        asm("hlt");
    }


    return 0;
    
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
    page* myPage;
    uint32 newAddr;
    
    dir->tables[address / ENTERY_SIZE] = (page_table *)malloc_ap(sizeof(page_table), &newAddr);
    memset(dir->tables[address / ENTERY_SIZE], 0, OFFSET_LEN);
    dir->tablesPhysicalAdrs[address / ENTERY_SIZE] = newAddr | 0x7;

    myPage = &dir->tables[address / ENTERY_SIZE]->pages[address % ENTERY_SIZE];
    
    for (uint32 i = 0; i < 1024; i++)
    {
        dir->tables[address / ENTERY_SIZE]->pages[i].present = 0;
    }

    return myPage;
}


void clear_page(uint32 address)
{
    page *p = get_page(address, false, kernel_directory);
    if(p) {
        freeFrame(p);
    }
}



#include "../include/paging.h"
#define OFFSET_LEN 0x1000

struct page_directory *kernel_directory;
struct page_directory *current_directory;



/*
the function sets up the paging in the memory
total_frames: gets the total amount of frames (using the bootloader)
ret: none
*/

void initialize_paging(unsigned_int32 total_frames) {

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

struct page *get_page(unsigned_int32 address, struct page_directory *dir)
{
    // removes the files offset from the address by shifting the address using division of the necessery amount of bits
    address /= OFFSET_LEN;
    // Find the page table containing this address
    unsigned_int32 table_idx = address / 1024;
    if (dir->tables[table_idx] != 0) // If this table is already assigned in the table
    {
        //returns the page in the correct table and page
        return &dir->tables[table_idx]->pages[address % 1024];
    }
    else
    {
        return 0;
    }
}
#include "../include/paging.h"

struct page_directory *kernel_directory;
struct page_directory *current_directory;


void initialize_paging() {

    current_directory = kernel_directory;
    
    // Go ahead and allocate all the page tables for the kernel.
    // This is wasteful, but a lot easier than figuring out how to build
    // a kernel page allocator.
    unsigned_int32 i = 0;
    enablePaging();
    loadPageDirectory(kernel_directory);

}

struct page *get_page(unsigned_int32 address, int makeNew, struct page_directory *dir)
{
    // removes the files offset from the address by shifting the address using division of the necessery amount of bits
    address /= 0x1000;
    // Find the page table containing this address
    unsigned_int32 table_idx = address / 1024;
    if (dir->tables[table_idx] != 0) // If this table is already assigned in the table
    {
        //returns the page in the correct table and page
        return &dir->tables[table_idx]->pages[address%1024];
    }
    else if(makeNew)
    {
        //allocats a new page in the address
    }
    else
    {
        return 0;
    }
}
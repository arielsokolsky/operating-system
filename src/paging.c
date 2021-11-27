#include "../include/paging.h"





struct page *get_page(uint32_t address, int makeNew, struct page_directory *dir)
{
    // removes the files checksum from the address by shifting the address using division of the necessery amount of bits
    address /= 0x1000;
    // Find the page table containing this address
    unsigned_int32 table_idx = address / 1024;
    if (dir->tables[table_idx] != NULL) // If this table is already assigned in the table
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
        return NULL;
    }
}
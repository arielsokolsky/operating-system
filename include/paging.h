#ifndef PAGING_H
#define PAGING_H
#include "types.h"

struct page {
    //checks if the file exists
    unsigned_int8 present : 1; 
    // if the bit is clear then the file is read only, if the bit is one then it read and write
    unsigned_int8 readwrite : 1;
    // says the file supervision level
    unsigned_int8 user : 1;
    // Has the page been accessed since the last os refresh?
    unsigned_int8 lastAccessed : 1; 
    //Has the page been written into since the last user os refresh?
    unsigned_int8 lastWritten : 1;   
    // unused bits and flags
    unsigned_int8 unusedBits : 7;   
    // Frame address
    unsigned_int32 frameAddress : 20;  
};


struct page_table
{
    struct page pages[1024];
};

struct page_directory
{
    struct page_table *tables[1024];

    unsigned_int32 tablesPhysicalAdrs[1024];

    unsigned_int32 physicalAddress;
};

struct page *get_page(uint32_t address, int makeNew, struct page_directory *dir);
#endif
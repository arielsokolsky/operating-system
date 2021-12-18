#ifndef PAGING_H
#define PAGING_H
#include "types.h"
#define OFFSET_LEN 0x1000
#define ENTERY_SIZE 0x400

typedef struct page {
    //checks if the file exists
    _Bool present; 
    // if the bit is clear then the file is read only, if the bit is one then it read and write
    _Bool readwrite;
    // says the file supervision level
    _Bool user;
    // Has the page been accessed since the last os refresh?
    _Bool lastAccessed; 
    //Has the page been written into since the last user os refresh?
    _Bool lastWritten;   
    // unused bits and flags
    unsigned_int8 unusedBits : 7;   
    // Frame address
    unsigned_int32 frameAddress : 20;  
}page;

unsigned_int32 _physicalAddr;

extern void enablePaging();
extern void loadPageDirectory(unsigned_int32);

typedef struct page_table
{
    struct page pages[1024];
}page_table;

typedef struct page_directory
{
    page_table *tables[1024];

    unsigned_int32 tablesPhysicalAdrs[1024];

    unsigned_int32 physicalAddress;
}page_directory;

page_directory *kernel_directory;
page_directory *current_directory;


void initialize_paging();
page *get_page(unsigned_int32 address, page_directory *dir);
#endif
#ifndef PAGING_H
#define PAGING_H
#include "types.h"
#include "malloc.h"
#include "screen.h"
#include "input.h"
#define OFFSET_LEN 0x1000
#define ENTERY_SIZE 0x400
#define MAX_ADDRESS OFFSET_LEN * ENTERY_SIZE * ENTERY_SIZE


extern uint32 currentAddress;

typedef struct page 
{
    //checks if the file exists
    uint32 present : 1; 
    // if the bit is clear then the file is read only, if the bit is one then it read and write
    uint32 readwrite : 1; 
    // says the file supervision level
    uint32 user : 1; 
    // Has the page been accessed since the last os refresh?
    uint32 lastAccessed : 1;
    //Has the page been written into since the last user os refresh?
    uint32 lastWritten : 1; 
    // unused bits and flags
    uint32 unusedBits : 7;   
    // Frame address
    uint32 frameAddress : 20;  
}page;

static uint32 _physicalAddr;


typedef struct page_table
{
    page pages[1024];
}page_table;

typedef struct page_directory
{
    page_table *tables[1024];

    uint32 tablesPhysicalAdrs[1024];

    uint32 physicalAddress;
}page_directory;

static page_directory *kernel_directory;
static page_directory *current_directory;

void switch_page_directory(page_directory * addr);
void initialize_paging(uint32);
page *get_page(uint32 address, bool make, page_directory *dir);
page* getPageByFrame(uint32 frameAddress);
page* mapPage(uint32 address);
page *make_page(uint32 address, page_directory *dir);
void clear_page(uint32 address);
extern void enablePaging();

#endif
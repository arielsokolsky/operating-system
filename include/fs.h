#ifndef FS_H
#define FS_H

#include "ata.h"

#define MAX_NAME_LEN 20
#define ROOT_ADDRESS 0

typedef struct node
{
    char name[MAX_NAME_LEN];
    uint32 address;//address of first fragmentHeader
}__attribute__((packed)) node;

typedef struct fragmentHeader
{
    uint32 dataLen;
    uint32 nextAddress; 
}__attribute__((packed)) fragmentHeader;

static uint32 freeAddress;


//function's: create and remove files
node writeFile(string name, string data);

//function's: read from fragments
void readFragments(uint32 address, void* data, uint32 dataLen, uint32 startAddress);

//function's: find fragments
void findNextHeader(fragmentHeader head, fragmentHeader* next);
uint32 findLastHeader(uint32 address);
uint32 findFragment(uint32 headAddress, int len);

//function's: add a new fragment
uint32 addFragment(void* data, int len);
void addFooter(uint32 address, uint32 newAddress);
void appendFragments(uint32 address, void* data, int len);
void pushFragments(uint32 currentHeaderAddress, void* data, int len);

//function's: converts
uint32 replaceFragmentsData(uint32 address, void* data, uint32 len);
fragmentHeader getHeader(uint32 address);

//function's: store and save
void save();
void loadFs();

#endif
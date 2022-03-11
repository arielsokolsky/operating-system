#ifndef FS_H
#define FS_H

#include "ata.h"

#define MAX_NAME_LEN 20


typedef struct node
{
    char name[MAX_NAME_LEN];
    uint32 address;//address of first fragmentHeader
}__attribute__((packed)) node;

typedef struct fragmentHeader
{
    uint32 address;
    uint32 dataLen;
    uint32 nextAddress; 
}__attribute__((packed)) fragmentHeader;

static uint32 freeAddress;


//function's: create and remove files
node writeFile(string name, string data);

//function's: add and remove fragments
uint32 addFragment(string data);
void readFragments(uint32 address, char* data);

//function's: find and move fragments
void findNextHeader(fragmentHeader head, fragmentHeader* next);
uint32 findLastHeader(uint32 address);

//connection a new fragment
void addFooter(uint32 address, uint32 newAddress);
void appendFragments(uint32 address, string data);

//function's: converts
fragmentHeader getHeader(uint32 address);

//function's: store and save
void save();
void loadFs();

#endif
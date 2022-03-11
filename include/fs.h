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

fragmentHeader getHeader(uint32 address);

uint32 addFragment(string data);
void readFragments(uint32 address, char* data);

node writeFile(string name, string data);

void findNextHeader(fragmentHeader head, fragmentHeader* next);
uint32 findLastHeader(uint32 address);

void addFooter(uint32 address, uint32 newAddress);
void appendFragments(uint32 address, string data);

void createDir();
void save();
void loadFs();

#endif
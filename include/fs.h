#ifndef FS_H
#define FS_H

#include "ata.h"

#define MAX_NAME_LEN 20


typedef struct node
{
    char name[MAX_NAME_LEN];
    uint32 address;//address of first fragmentHeader
}node;

//
typedef struct fragmentHeader
{
    uint32 address;//address of first fragmentHeader
    uint32 dataLen;
    uint32 nextAddress; 
}__attribute__((packed)) fragmentHeader;

static uint32 freeAddress;

fragmentHeader addFragment(string data);
void continueFile(fragmentHeader* head, string data);
void readFile(fragmentHeader head, char* data);
void addFooter(fragmentHeader* last, uint32 address);
void findNextHeader(fragmentHeader head, fragmentHeader* next);
void findLastHeader(fragmentHeader head, fragmentHeader* last);
void createDir();
void save();
void loadFs();

#endif
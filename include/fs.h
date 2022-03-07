#ifndef FS_H
#define FS_H

#include "ata.h"

#define MAX_NAME_LEN 20

typedef struct header
{
    uint32 address;
    int dataLen;
    char name[MAX_NAME_LEN];
    header* next; 
}header;

void createFile();
void createDir();
void save();
void load();

#endif
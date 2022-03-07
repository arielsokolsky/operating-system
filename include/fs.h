#ifndef FS_H
#define FS_H

#include "ata.h"

#define MAX_NAME_LEN 20

typedef struct header{
    char name[MAX_NAME_LEN];
    uint32 address;
    uint32 dataLen;
    uint32* nextAddress; 
}__attribute__((packed)) header;

static uint32 freeAddress;

void createFile(string name, string path, string data);
void readFile(header* head, char* data);
header* findNextHeader(header* head);
header findlast(header head);
void createDir();
void save();
void loadFs();

#endif
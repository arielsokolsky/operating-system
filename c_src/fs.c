#include "../include/fs.h"


void createFile(string name, string path, string data)
{
    header currentHeader;
    uint32 dataLen = strlen(data);
    string fullPath;
    
    //add the path and the name
    strcpy(fullPath, path);
    strcpy(fullPath + strlen(path), "/");
    strcpy(fullPath + strlen(path) + 1, name);

    //set the struct
    strcpy(currentHeader.name, fullPath);
    currentHeader.dataLen = dataLen;
    currentHeader.address = freeAddress + sizeof(header);
    currentHeader.nextAddress = 0; 

    write(freeAddress, sizeof(header), &currentHeader);
    freeAddress += sizeof(header);

    write(freeAddress, dataLen, data);
    freeAddress += dataLen;
}

/*
the function get root directory
return: none
*/
void loadFs()
{
    freeAddress = 0;

    //get all the data from root dir
}

/*
the function read file 
param head: all the data needed to read the file
return: none
*/
void readFile(header* head, char* data)
{
    char* bytes;

    read(bytes, head->address, head->dataLen);
    strcpy(data, bytes);
    data += head->dataLen;

    if(head->nextAddress == 0)
    {
        return;
    }
    readFile(findNextHeader(head), data);
}

/*
the function get the header
param head: the head we find the next
return: the next header of head
*/
header* findNextHeader(header* head)
{
    header* next;
    read(next, head->nextAddress, sizeof(header));
    return next;
}



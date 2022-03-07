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
    currentHeader.next = 0; 



    write(freeAddress, sizeof(header), &currentHeader);
    freeAddress += sizeof(header);

    write(freeAddress, dataLen, data);
    freeAddress += dataLen;
}

void loadFs()
{
    freeAddress = 0;

    //get all the data from root dir
}



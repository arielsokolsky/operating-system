#include "../include/fs.h"


header createFile(string name, string path, string data)
{
    header head;
    uint32 dataLen = strlen(data);
    string fullPath;
    
    //add the path and the name
    strcpy(fullPath, path);
    strcpy(fullPath + strlen(path), "/");
    strcpy(fullPath + strlen(path) + 1, name);

    //set the struct
    strcpy(head.name, fullPath);
    head.dataLen = dataLen;
    head.address = freeAddress + sizeof(header);
    head.nextAddress = 500; 

    write(freeAddress, sizeof(header), &head);
    freeAddress += sizeof(header);

    write(freeAddress, dataLen, data);
    freeAddress += dataLen;


    
    header nextHeader;
    //set the next struct
    string newData = "but still didn't finish";
    strcpy(nextHeader.name, fullPath);
    nextHeader.dataLen = strlen(newData);
    nextHeader.address = 500 + sizeof(header);
    nextHeader.nextAddress = 0; 

    //write the header
    write(500, sizeof(header), &nextHeader);

    //write the data
    write(nextHeader.address, nextHeader.dataLen, newData);
    

    return head;
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
    //get the data and copy to var
    read(bytes, head->address, head->dataLen);
    strcpy(data, bytes);
    
    //check if got to the end
    if(head->nextAddress == 0)
    {
        //set the last byte of the string as 0
        data[head->dataLen] = 0;
        return;
    }
    //move the variable
    data += head->dataLen;

    //find the next header and pass it
    header* next = findNextHeader(head);
    readFile(next, data);
}

/*
the function get the header
param head: the head we find the next
return: the next header of head
*/
header* findNextHeader(header* head)
{
    header* next;
    if(head->nextAddress == 0)
    {
        return 0;
    }
    read(next, head->nextAddress, sizeof(header));
    return next;
}



#include "../include/fs.h"


/*
the function craete a file
param name: the name of the file
param path: the path of the file
param data: the data of the file
return: the header of the file
*/
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
    nextHeader.nextAddress = 600; 

    //write the header
    write(500, sizeof(header), &nextHeader);

    //write the data
    write(nextHeader.address, nextHeader.dataLen, newData);

    
    header lastHeader;
    //set the next struct
    string dataNew = " unbelieveable it still continue";
    strcpy(lastHeader.name, fullPath);
    lastHeader.dataLen = strlen(dataNew);
    lastHeader.address = 600 + sizeof(header);
    lastHeader.nextAddress = 0; 

    //write the header
    write(600, sizeof(header), &lastHeader);

    //write the data
    write(lastHeader.address, lastHeader.dataLen, dataNew);
    

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
    uint32 address = head->address, len = head->dataLen;

    //get the data and copy to var
    read(bytes, address, len);

    strcpy(data, bytes);
    
    printInt(head->nextAddress);
    println("");

    //move the variable
    data += head->dataLen;
    
    //find the next header and pass it
    header* next;
    findNextHeader(*head, next);
    
    if(!next)
    {
        return;
    }

    readFile(next, data);
}

/*
the function get the header
param head: the head we find the next
param next: the next header of head
return: none
*/
void findNextHeader(header head, header* next)
{   
    if(head.nextAddress == 0)
    {
        *next = head;
        return;
    }
    
    read(next, head.nextAddress, sizeof(header));
}

/*
the function find the last node in the linked list
param head: the head of the list
param last: a pointer to the last node in the list
return: none
*/
void findLastHeader(header head, header* last)
{
    do
    {
        findNextHeader(head, last);  
        head = *last;
    }while(head.nextAddress != 0);
}

/*
the funtion add a new part to the file
param head: a part of the linked list
param address: where the last node will point to
return: none
*/
void addHeader(header* node, uint32 address)
{
    header* last;
    findLastHeader(*node, last);

    //edit the last header 
    node->nextAddress = address;

    //write it again
    write(node->address - sizeof(header), sizeof(header), node);
}


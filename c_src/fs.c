#include "../include/fs.h"

/*
the function write a file
param path: the file location and it's name
param data: the file data
return: the node (data about the file)
*/
node writeFile(string path, string data)
{
    node file;
    uint32 address;
    
    address = addFragment(data);

    strcpy(file.name, path);
    file.address = address;

    return file;
}

/*
the function craete a file
param data: the data of the file
return: the fragmentHeader of the file
*/
uint32 addFragment(string data)
{
    fragmentHeader head;
    uint32 dataLen = strlen(data);
    uint32 headerAddress;

    //set the struct
    head.dataLen = dataLen;
    head.address = freeAddress + sizeof(fragmentHeader);
    head.nextAddress = 0; 

    write(freeAddress, sizeof(fragmentHeader), &head);
    headerAddress = freeAddress;
    freeAddress += sizeof(fragmentHeader);

    write(freeAddress, dataLen, data);
    freeAddress += dataLen;

    return headerAddress;
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
the function read a fragment 
param head: the head of the linked list (belong to the file)
param data: where the info stored
return: none
*/
void readFragments(uint32 address, char* data)
{   
    fragmentHeader head = getHeader(address);
    fragmentHeader* next; 
    while(1)
    {
        //get the data from the head
        read(data, head.address, head.dataLen);

        //move the array by len
        data += head.dataLen;

        //there is no next
        if(head.nextAddress == 0)
        {
            //add the zero to the string
            data[0] = 0;
            return;
        }

        //change head to next
        findNextHeader(head, next);  
        head = *next;
    }
}

/*
the function get the fragmentHeader
param head: the head we find the next
param next: the next fragmentHeader of head
return: none
*/
void findNextHeader(fragmentHeader head, fragmentHeader* next)
{   
    if(head.nextAddress == 0)
    {
        *next = head;
        return;
    }
    
    read(next, head.nextAddress, sizeof(fragmentHeader));
}

/*
the function find the last node in the linked list
param head: the head of the list
param last: a pointer to the last node in the list
return: the last header address
*/
uint32 findLastHeader(uint32 address)
{
    fragmentHeader head = getHeader(address);
    fragmentHeader* last;
    uint32 lastAddress = 0;
    do
    {
        lastAddress = head.nextAddress;
        findNextHeader(head, last);  
        head = *last;
    }while(head.nextAddress != 0);

    return lastAddress;
}

/*
the funtion add a new part to the file
param head: a part of the linked list
param address: where the last node will point to
return: none
*/
void addFooter(uint32 address, uint32 newAddress)
{    
    fragmentHeader last = getHeader(address); 
    
    //edit the last fragmentHeader 
    last.nextAddress = newAddress;
    
    //write it again to disk
    write(address, sizeof(fragmentHeader), &last);
}

/*
the function append fragment to linked list
param address: address of header in linked list
param data: the data of the new fragment
return: none
*/
void appendFragments(uint32 address, string data)
{
    //get last header address
    uint32 lastAddress = findLastHeader(address);

    //set the struct values
    address = addFragment(data);
    
    //change last header
    addFooter(lastAddress, address);
}

/*
the function get header by address
param address: the address of header
return: the header
*/
fragmentHeader getHeader(uint32 address)
{
    fragmentHeader head;
    read(&head, address, sizeof(fragmentHeader));
    return head;
}



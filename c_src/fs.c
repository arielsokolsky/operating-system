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
    
    //address = addFragment(data);

    strcpy(file.name, path);
    file.address = address;

    return file;
}

/*
the function craete a file
param data: the data of the file
return: the fragmentHeader of the file
*/
uint32 addFragment(void* data, int len)
{
    fragmentHeader head;
    uint32 headerAddress;

    //set the struct
    head.dataLen = len;
    head.nextAddress = 0; 

    write(freeAddress, sizeof(fragmentHeader), &head);
    headerAddress = freeAddress;
    freeAddress += sizeof(fragmentHeader);

    if(len > 0)
    {
        write(freeAddress, len, data);
        freeAddress += len;
    }


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
param address: the address of head of linked list
param data: where the info stored
param dataLen: the len which to read
return: none
*/
void readFragments(uint32 address, string data, uint32 dataLen)
{   
    uint32 currentAddress = address + sizeof(fragmentHeader);
    fragmentHeader head = getHeader(address);
    fragmentHeader* next; 
    int len = 0;

    //if true then read all the file
    bool readAll = (dataLen == 0 ? true : false);


    while(true)
    {
        len = head.dataLen;
        //check if got to max len
        if(dataLen < len && readAll == false)
        {
            len = dataLen;
        }

        //get the data from the head
        read(data, currentAddress, len);

        //move the array by len
        data += len;
        dataLen -= len;
        //there is no next
        if(head.nextAddress == 0)
        {
            //add the zero to the string
            data[0] = 0;
            return;
        }

        currentAddress = head.nextAddress + sizeof(fragmentHeader);

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
    //if head doesn't have next
    if(head.nextAddress == 0)
    {
        return address;
    }
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
void appendFragments(uint32 address, void* data, int len)
{
    //set the struct values
    uint32 newAddress = addFragment(data, len);
    //get last header address
    address = findLastHeader(address);
    //change last header
    addFooter(address, newAddress);
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



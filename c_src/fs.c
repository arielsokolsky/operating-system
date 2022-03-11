#include "../include/fs.h"


/*
the function craete a file
param name: the name of the file
param path: the path of the file
param data: the data of the file
return: the fragmentHeader of the file
*/
fragmentHeader addFragment(string fullPath, string data)
{
    fragmentHeader head;
    uint32 dataLen = strlen(data);
    
    //add the path and the name
    //strcpy(fullPath, path);
    //strcpy(fullPath + strlen(path), "/");
    //strcpy(fullPath + strlen(path) + 1, name);

    //set the struct
    strcpy(head.name, fullPath);
    head.dataLen = dataLen;
    head.address = freeAddress + sizeof(fragmentHeader);
    head.nextAddress = 0; 

    write(freeAddress, sizeof(fragmentHeader), &head);
    freeAddress += sizeof(fragmentHeader);

    write(freeAddress, dataLen, data);
    freeAddress += dataLen;




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
the function read a file 
param head: the head of the linked list (belong to the file)
param data: where the info stored
return: none
*/
void readFile(fragmentHeader head, char* data)
{   
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
return: none
*/
void findLastHeader(fragmentHeader head, fragmentHeader* last)
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
void addFooter(fragmentHeader* last, uint32 address)
{    
    fragmentHeader var;
    
    //edit the last fragmentHeader 
    last->nextAddress = address;
    
    //write it again to disk
    write(last->address - sizeof(fragmentHeader), sizeof(fragmentHeader), last);
    
    //change the varable
    //findLastHeader(var, last);
}

void continueFile(fragmentHeader* last, string data)
{
    fragmentHeader currentHeader;
    string name = last->name;
    uint32 headAddr; 

    //TO DO: FIND LAST HEADER

    //set the struct values
    currentHeader = addFragment(name, data);
    
    addFooter(last, currentHeader.address - sizeof(fragmentHeader));
}
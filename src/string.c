#include "../include/types.h"

/*
the fuction return string length
param: str
return: the str length
*/
int strlen(string str)
{
    int i = 0;
    while(str[i++]);  
    return i-1;
}

/*
the fuction get 2 string and return if equel
param: 2 strings
return: if string equel
*/
bool strcmp(string str1, string str2)
{
    bool equel = true;

    //check if length equel
    if(strlen(str1) != strlen(str2))
        equel = false;

    //check that string the same
    for(int i = 0; i < strlen(str1); i++)
    {
        if(str1[i] != str2[i])
            equel = false;
    } 

    return equel;
}
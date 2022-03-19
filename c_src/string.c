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
the function copy one string to the other
param str1: the first string(src)
param str2: the second string(dst)
return: none
*/
void strcpy(string dest, string source)
{
    int i = 0;
    for (i = 0; i < strlen(source) + 1; i++)
    {
        dest[i] = source[i];
    }
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



/*
the function revers string
param: string
return: the string reversed
*/
string strrev(string str)
{
    string reversedString = "";
    int len = strlen(str);
    int end = len - 1;
    int i = 0;

    for (i = 0; i < len; i++) 
    {
        reversedString[i] = str[end];
        end--;
    }

    reversedString[i] = '\0';


    return reversedString;
}



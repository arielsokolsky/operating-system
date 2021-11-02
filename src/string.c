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

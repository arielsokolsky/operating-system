#include "../include/types.h"

unsigned_int16 strlen(string str)
{
    unsigned_int16 i = 0;
    while(str[i++]);  
    return i-1;
}

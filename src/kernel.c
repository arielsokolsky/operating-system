#include "../include/string.h"
#include "../include/types.h"

int main()
{
    string a = "sadf";
    
  
    *((int*)0xb8000 ) = 0x07690748;
    *((int*)(0xb8000 + 1))= 3;
    

    return 0;
}

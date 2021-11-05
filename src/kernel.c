#include "../include/string.h"
#include "../include/types.h"
#include "../include/screen.h"
#include "../include/input.h"
#include "../include/convert.h"


int main()
{
    int a[4] = {2, 4, 5, 5};
    printWelcomeScreen();
    //readString();
    printArr(a);
    
    return 0;
}

/*
the function print the welcome screen
param: none
return: none
*/

void printWelcomeScreen()
{
    clearScreen();
    changeTextColor(White);
    print("welcome to our os \n");
    print("the os is very effective with memory\n\n");
}
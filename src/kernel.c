#include "../include/string.h"
#include "../include/types.h"
#include "../include/screen.h"
#include "../include/input.h"
#include "../include/convert.h"
#include "../include/shell.h"

int main()
{
    clearScreen();//printWelcomeScreen();

    for (int i = 0; i <= 25; i++)
    {
        print("sa\n");
    }
    readString();
    
    //runTerminal();
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
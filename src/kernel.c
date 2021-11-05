#include "../include/string.h"
#include "../include/types.h"
#include "../include/screen.h"
#include "../include/input.h"
#include "../include/convert.h"
#include "../include/calculator.h"

int main()
{
    printWelcomeScreen();
    /*
    string str;
    while (1)
    {
        str = readString();
        print("\n");
        printInt(fibonacci(stringToInt(str)));
        print("\n");
    }*/
    


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
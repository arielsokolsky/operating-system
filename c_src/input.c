#include "../include/input.h"

/*
the function gets the user input
param: none
return: the user input
*/
string readString()
{
    char allLetters[] = {0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 0, 0 \
    , 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', 0, 0 \
    , 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', 0, 0, 0 \
    , 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', '.', '/', 0, ' '};
    char buffstr[200];  
    int i = 0; //the last place in the string
    bool is_reading = true; // if the system is reading input, it is 1, and if it stops, its 0
    while (is_reading)
    {
        if(inputPort(CHECK_PORT) & 0x1) //checks if there is an input from the user
        {
            int letterNum = inputPort(READ_PORT) ;
            if (letterNum == 28)
            {
                is_reading = false;
            }
            else if(letterNum == 14)
            {
                i--;
                buffstr[i] = 0;
                backSpace();
            }
            else if(allLetters[letterNum] && letterNum < 60)
            {  
                printch(allLetters[letterNum]);
                buffstr[i] = allLetters[letterNum];
                i++;
            }
        }
    }
    buffstr[i] = 0;
    string str = (string)buffstr;
    print("\n");
    return str;
}
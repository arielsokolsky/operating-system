#include "../include/input.h"

#define MAX_COMMAND_LEN 20
#define MAX_COMMANDS 20

#define MAX_PARAM_LEN 50
#define MAX_PARAM 30

#define UP_ARROW 72 
#define DOWN_ARROW 80
#define ENTER 28

uint8 length = 0, currentCommand = 0;
static char commandsList[MAX_COMMANDS][MAX_COMMAND_LEN] = {0};


/*
the function gets the user input
param: none
return: the user input
*/
string readString()
{
    int letterNum = 0;
    int isInput = 0;
    char allLetters[] = {0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 0, 0 \
    , 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', 0, 0 \
    , 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', 0, 0, 0 \
    , 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', '.', '/', 0, ' '};
    char buffstr[200] = {0}; 
    
    int i = 0; //the last place in the string
    bool is_reading = true; // if the system is reading input, it is 1, and if it stops, its 0
    while (is_reading)
    {
        if(inputPort(CHECK_PORT) & 0x1) //checks if there is an input from the user
        {
            letterNum = inputPort(READ_PORT);

            
            if (letterNum == ENTER)
            {
                is_reading = false;
            }
            else if(letterNum == UP_ARROW && length > 0)
            {
                deleteCommand(i);
                if(currentCommand < length)
                {
                    currentCommand++;
                }
                print(commandsList[currentCommand]);
                strcpy(buffstr, commandsList[currentCommand]);
                i = strlen(buffstr); 
            }
            else if(letterNum == DOWN_ARROW && length > 0)
            {
                deleteCommand(i);
                if(currentCommand > 0)
                {
                    currentCommand--;
                }
                print(commandsList[currentCommand]);
                strcpy(buffstr, commandsList[currentCommand]);
                i = strlen(buffstr);
            }
            else if(letterNum == 14)
            {
                if (i != 0)
                {
                i--;
                buffstr[i] = 0;
                backSpace();
                }
            }
            else if(allLetters[letterNum] && letterNum < 65)
            {  
                printch(allLetters[letterNum]);
                buffstr[i] = allLetters[letterNum];
                i++;
            }
        }
    }
    buffstr[i] = 0;

    if(buffstr[0] != 0 && isCommand == 1)
    {
        strcpy(commandsList[length], buffstr);  
        currentCommand = length; 
        length++;
    }
    
    string str = buffstr;
    print("\n");
    return str;
}


void deleteCommand(int len)
{
    for (int i = 0; i < len; i++)
    {
        backSpace();
    }
    
}




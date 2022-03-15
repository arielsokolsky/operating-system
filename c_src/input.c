#include "../include/input.h"

string commands[200];
uint8 length = 0;

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
    /*if(length > 3)
    {
        print(commands[3]); 
    }*/
    
    //printInt(length);
    int i = 0, current_command = length; //the last place in the string
    bool is_reading = true; // if the system is reading input, it is 1, and if it stops, its 0
    while (is_reading)
    {
        if(inputPort(CHECK_PORT) & 0x1) //checks if there is an input from the user
        {
            int letterNum = inputPort(READ_PORT) ;
            //printInt(letterNum);
            
            if (letterNum == 28)
            {
                is_reading = false;
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
                if (allLetters[letterNum] == 'p')
                {
                    for (int j = 0; j < length; j++)
                    {
                        print(commands[current_command]);
                        printch('\n');
                    } 
                }
                buffstr[i] = allLetters[letterNum];
                i++;
            }
            else if(letterNum == 80 || letterNum == 72)
            {  
                if(isInTerminal)
                {
                    if (((letterNum == 72) && (current_command > 0)) || ((letterNum == 80) && (current_command < length)))
                    {
                        for (int j = 0; j < i; j++)
                        {
                            buffstr[j] = 0;
                        }
                        for (; i > 0; i--)
                        {
                            backSpace();
                        }
                        if(letterNum == 72)
                        {
                            current_command--;
                        }
                        else if (letterNum == 80)
                        {
                            current_command++;
                        }
                        print(commands[current_command]);
                        i = strlen(commands[current_command]);
                        
                        for (int j = 0; j < i; j++)
                        {
                            buffstr[j] = commands[current_command][j];
                        } 
                    }
                }
            }
        }
    }
    buffstr[i] = 0;
    
    //commands[length] = (string)malloc(i);
    for (int j = 0; j < i; j++)
    {
        commands[length][j] = buffstr[j];
    }
    
    string str = buffstr;
    length++;
    print("\n");
    return str;
}
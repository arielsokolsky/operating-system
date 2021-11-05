#include "../include/shell.h"
/*
the funtion start a terminal that handle user resquest
param: none
return: none
*/
void runTerminal()
{
    while (true)
    {
        string input = "";
        print(">> ");
        string command = readString();
        print("\n");
        if (strcmp(command, "help"))
        {
            help();
        }
        else if (strcmp(command, "echo"))
        {
            print("enter text: ");
            input = readString();
            print("\n");
            print(input);    
        }
        else if (strcmp(command, "sum"))
        {
            
        }
        else if (strcmp(command, "sub"))
        {
            
        }
        else if (strcmp(command, "exit"))
        {   
            return;
        }
        else if (strcmp(command, "text-color"))
        {
            printColors();
            print("enter color number: ");
            input = readString();
            changeTextColor(stringToInt(input) - 1);
        }
        else if (strcmp(command, "fibonacci"))
        {
            
        }
        else
        {
            print("command doesn't exist");
        }
        
        print("\n");
    }
    
}

void help()
{
    print("command list:\n");
    print("help - get all command");
    print("echo - print to screen \n");
    print("sum - add n of numbers\n");
    print("sub - substruct n of numbers\n");
    print("exit - stop running\n");
    print("text-color - change text color\n");
    print("fibonacci - find n number entery in the fibonacci serious\n");
}

void printColors()
{
    print("1.Black\n"); 
    print("2.Blue\n");
    print("3.Green\n");
    print("4.Cyan\n");
    print("5.Red\n");
    print("6.Purple\n");
    print("7.Brown\n");
    print("8.Gray\n");
    print("9.Dark_gray\n");
    print("10.Light_blue\n");
    print("11.light_green\n");
    print("12.Light_cyan\n");
    print("13.Light_Red\n");
    print("14.light_purple\n");
    print("15.Yellow \n");
    print("16.White\n");
}


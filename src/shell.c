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
        //else if (strcmp(command, "sum"))
        //{
            
        //}
        
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
    print("change text color\n");
    print("fibonacci\n");
}
#include "../include/shell.h"
/*
the funtion start a terminal that handle user resquest
param: none
return: none
*/
void runTerminal()
{
    string input = "", command = "";
    int result = 0, len = 0;
    int array[20];
    

    while (true)
    {
        input = "";
        print(">> ");
        string command = readString();
        print("\n");

        if (strcmp(command, "help"))
        {
            help();
        }
        else if (strcmp(command, "clear"))
        {
            clearScreen();
        }
        else if (strcmp(command, "echo"))
        {
            print("enter text: ");
            input = readString();
            print("\n");
            print(input);    
        }
        else if (strcmp(command, "string-reverse"))
        {
            print("enter string: ");
            input = readString();
            print("\n");
            print("the string reversed: ");
            print(strrev(input));
        }
        else if (strcmp(command, "sort"))
        {   
            print("enter number of numbers: ");
            len = stringToInt(readString());
            print("\n");
            for (int i = 0; i < len; i++)
            {
                print("enter number: ");
                array[i] = stringToInt(readString());
                print("\n");
            }
            sort(array, len);   
            printArr(array, len);

        }   
        else if (strcmp(command, "sum"))
        {
            print("enter how many number: ");
            input = readString();
            len = stringToInt(input);
            print("\n");

            for (int i = 0; i < len; i++)
            {
                print("enter number: ");
                input = readString();
                print("\n");
                array[i] = stringToInt(input);
            }
            result = sum(array, len);
            printInt(result);
        }
        else if (strcmp(command, "sub"))
        {
            print("enter how many number: ");
            input = readString();
            len = stringToInt(input);
            print("\n");

            for (int i = 0; i < len; i++)
            {
                print("enter number: ");
                input = readString();
                print("\n");
                array[i] = stringToInt(input);
            }
            result = sub(array, len);
            printInt(result);
        }
        else if (strcmp(command, "fibonacci"))
        {
            print("enter fibonacci entery: ");
            input = readString();
            print("\n");

            result = fibonacci(stringToInt(input));   
            print(intToString(result));  
        } 
        else if (strcmp(command, "text-color"))
        {
            printColors();
            print("enter color number: ");
            input = readString();
            changeTextColor(stringToInt(input) - 1);
        }
        else if (strcmp(command, "exit"))
        {   
            return;
        }  
        else
        {
            print("error: command not found");
        }
        
        print("\n");
    }
    
}

void help()
{
    print("command list:\n");
    print("help - get all command");
    print("clear - clear screen");
    print("echo - print to screen \n");
    print("string-reverse - reverse a string\n");
    print("sort - sort array of numbers");
    print("sum - add n of numbers\n");
    print("sub - substruct n of numbers\n");
    print("fibonacci - find n number entery in the fibonacci serious\n");
    print("text-color - change text color\n");
    print("exit - stop running\n");
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


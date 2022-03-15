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
    
    
    isInTerminal = true;
    while (true)
    {
        input = "";
        print(">> ");
        string command = readString();

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
            println(input);    
        }
        else if (strcmp(command, "string-reverse"))
        {
            print("enter string: ");
            input = readString();
            print("the string reversed: ");
            println(strrev(input));
        }
        else if (strcmp(command, "sort"))
        {   
            print("enter number of numbers: ");
            len = stringToInt(readString());

            for (int i = 0; i < len; i++)
            {
                print("enter number: ");
                array[i] = stringToInt(readString());
            }
            sort(array, len);   
            printArr(array, len);
            print("\n");

        }   
        else if (strcmp(command, "sum"))
        {
            print("enter how many number: ");
            input = readString();
            len = stringToInt(input);

            for (int i = 0; i < len; i++)
            {
                print("enter number: ");
                input = readString();
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

            for (int i = 0; i < len; i++)
            {
                print("enter number: ");
                input = readString();
                array[i] = stringToInt(input);
            }
            result = sub(array, len);
            printInt(result);
        }
        else if (strcmp(command, "fibonacci"))
        {
            print("enter fibonacci entery: ");
            input = readString();

            result = fibonacci(stringToInt(input));   
            println(intToString(result));  
        } 
        else if (strcmp(command, "text-color"))
        {
            printColors();
            print("enter color number: ");
            input = readString();
            changeTextColor(stringToInt(input) - 1);
        }
        else if (strcmp(command, "background-color"))
        {
            printColors();
            print("enter color number: ");
            input = readString();
            changeBackgoundColor(stringToInt(input) - 1);
        }
        else if (strcmp(command, "devide"))
        {   

            for (int i = 0; i < 2; i++)
            {
                print("enter number: ");
                input = readString();
                array[i] = stringToInt(input);
            }
            result = array[0] / array[1];
            printInt(result);
        }
        else if (strcmp(command, "exit"))
        {   
            return;
        }  
        else
        {
            println("error: command not found");
        }
    }
    
}

void help()
{
    println("command list:");
    println("help - get all command");
    println("clear - clear screen");
    println("echo - print to screen ");
    println("string-reverse - reverse a string");
    println("sort - sort array of numbers");
    println("sum - add n of numbers");
    println("sub - substruct n of numbers");
    println("fibonacci - find n number entery in the fibonacci serious");
    println("text-color - change text color");
    println("devide -  deviding two numbers");
    println("exit - stop running");
}

void printColors()
{
    println("1.Black"); 
    println("2.Blue");
    println("3.Green");
    println("4.Cyan");
    println("5.Red");
    println("6.Purple");
    println("7.Brown");
    println("8.Gray");
    println("9.Dark_gray");
    println("10.Light_blue");
    println("11.light_green");
    println("12.Light_cyan");
    println("13.Light_Red");
    println("14.light_purple");
    println("15.Yellow ");
    println("16.White");
}


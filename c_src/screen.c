#include "../include/screen.h"

const uint8 char_limit = 80, BACKSPACE_KEY = 0x08, bytes_in_char = 2; //the character limit in a line is 80

/*
the fuction print char
param: char
return: none
*/
void printch(char ch)
{
    string video_memory = (string) VIDEO_ADDRESS;
    if(curY >= NUM_OF_LINES)
    {
        clearScreen();
    }
    switch(ch)
    {
        case(0x08): //when the user clicks backspace, make the the last chacter in screen blank
            if (curX > 0)
            {
                curX--; //go one character back
                video_memory[((curY * char_limit) + curX)*bytes_in_char] = 0; //delete the last character
            }
            break;
        case ('\n'): /* in case if there is an '\n' we will go one line 
        forward and will start from new in this line*/
            curX = 0;
            curY++;
            break;
        default:
            video_memory[((curY * char_limit) + curX)*bytes_in_char] = ch;
            video_memory[((curY * char_limit) + curX)*bytes_in_char + 1] = currentColor;
            curX++;
            break;
    }
    if (curX >= char_limit)
    {
        curX = 0;
        curY++;
    }
}

/*
the fuction print a string
param: string
return: none
*/
void print(string str)
{
    uint16 length = strlen(str);
    for (uint16 i = 0; i < length; i++)
    {
        printch(str[i]);
    }
}

/*
the function print a string and a new line at the end
param: string
return: none
*/
void println(string str)
{
    print(str);
    print("\n");
}

/*
the fuction change text color
param: the number of the color
return: none 
*/
void changeTextColor(int colorNum)
{
    currentColor = colorNum;
}

/*
the fuction clear the screen
param: none
return: none
*/
void clearScreen()
{
    curX = 0;
    curY = 0;
    for(int i = 0; i < NUM_OF_RAWS * NUM_OF_LINES; i++)
    {
        printch(' ');
    }
    curX = 0;
    curY = 0;
}


/*
the function print a int
param: int
return: none
*/
void printInt(int num)
{
    int a = num;
    string str = intToString(a);
    println(str);
}

/*
the function print array of int
param: array of int and it length
return: none
*/
void printArr(int* arr, int len)
{
    for(int i = 0; i < len; i++)
    {
        print(intToString(arr[i]));
        if(i != len - 1)
        {
            print(", ");
        }
        
    }
    println("");
}


/*
the function delete the last letter
param: none
return: none
*/
void backSpace()
{
    //check that not the start of a line
    if (curX == 0)
    {
        return;
    }
    //go back
    curX--;
    printch(' ');
    curX--;

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

/*
the function print the logo
param: none
return: none
*/
void printRhino()
{
    println("      __.--**\"\"\"**--...__..--**\"\"\"\"*-.           ");
    println("    .'                                `-.               ");
    println("  .'                         _           \\             ");
    println(" /                         .'        .    \\   _._      ");
    println(":                         :          :`*.  :-'.' ;      ");
    println(";    `                    ;          `.) \\   /.-'      ");
    println(":     `                             ; ' -*   ;          ");
    println("       :.    \\           :       :  :        :         ");
    println(" ;     ; `.   `.         ;     ` |  '                   ");
    println(" |         `.            `. -*\"*\\; /        :         ");
    println(" |    :     /`-.           `.    \\/`.'  _    `.        ");
    println(" :    ;    :    `*-.__.-*\"\"\":`.   \\ ;  'o` `. /     ");
    println("       ;   ;                ;  \\   ;:       ;:   ,/    ");
    println("  |  | |                       /`  | ,      `*-*'/      ");
    println("  `  : :  :                /  /    | : .    ._.-'       ");
    println("   \\  \\ ,  \\              :   `.   :  \\ \\   .'     ");
    println("    :  *:   ;             :    |`*-'   `*+-*            ");
    println("    `**-*`\"\"               *---*                      ");   
}






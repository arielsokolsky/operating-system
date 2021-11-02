#include "../include/screen.h"

int curX = 0, curY = 0;
const unsigned_int8 char_limit = 80, BACKSPACE_KEY = 0x08, bytes_in_char = 2; //the character limit in a line is 80

/*
the fuction print char
param: char
return: none
*/
void printch(char ch)
{
    string video_memory = (string) VIDEO_ADDRESS;
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
    unsigned_int16 length = strlen(str);
    for (unsigned_int16 i = 0; i < length; i++)
    {
        printch(str[i]);
    }
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
    for(int i = 0; i < NUM_OF_RAWS * NUM_OF_LINES; i++)
    {
        printch(' ');
    }
    curX = 0;
    curY = 0;
}


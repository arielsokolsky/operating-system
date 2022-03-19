#ifndef SCREEN_H
#define SCREEN_H

#include "string.h"
#include "convert.h"

#define VIDEO_ADDRESS 0xb8000
#define NUM_OF_LINES 25
#define NUM_OF_RAWS 80

enum COLORS{Black = 0, Blue, Green, Cyan, Red, Purple, Brown, Gray, Dark_gray, Light_blue, light_green, Light_cyan, Light_Red, light_purple, Yellow , White};
static int currentColor = White, currentBackground = Black;

typedef struct commands_list{
    string commands[255];
    uint8 length;
}command_list;

static uint8 curX = 0;
static uint8 curY = 0;

void printch(char ch);
void print(string str);
void changeTextColor(int);
void changeBackgoundColor(int colorNum);
void clearScreen();
void reprintBackground();
void printInt(int num);
void printIntln(int num);
void printArr(int* arr, int len);
void println(string str);
void backSpace();

void printRhino();
void printWelcomeScreen();

#endif
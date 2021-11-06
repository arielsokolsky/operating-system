#ifndef SCREEN_H
#define SCREEN_H

#include "string.h"
#include "convert.h"

#define VIDEO_ADDRESS 0xb8000
#define NUM_OF_LINES 25
#define NUM_OF_RAWS 80

enum COLORS{Black = 0, Blue, Green, Cyan, Red, Purple, Brown, Gray, Dark_gray, Light_blue, light_green, Light_cyan, Light_Red, light_purple, Yellow , White};
static int currentColor = White;

void printch(char ch);
void print(string str);
void changeTextColor(int);
void clearScreen();
void printInt(int num);
void printArr(int* arr, int len);
void backSpace();

#endif
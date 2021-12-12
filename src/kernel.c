#include "../include/string.h"
#include "../include/types.h"
#include "../include/screen.h"
#include "../include/input.h"
#include "../include/convert.h"
#include "../include/shell.h"
#include "../include/idt.h"
#include "../include/gdt.h"
#include "../include/malloc.h"

int main(multiboot_info* info)
{  
    int numFrames;
    printWelcomeScreen();
    setupIdt();
    install_gdt();
    print("\n");

    numFrames = printMultiBootInfo(info);
    readString();
    clearScreen();

    runTerminal();
    

    return 0;
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
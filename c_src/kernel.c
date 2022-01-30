#include "../include/string.h"
#include "../include/types.h"
#include "../include/screen.h"
#include "../include/input.h"
#include "../include/convert.h"
#include "../include/shell.h"
#include "../include/idt.h"
#include "../include/gdt.h"
#include "../include/paging.h"
#include "../include/malloc.h"
#include "../include/tss.h"
#include "../include/task.h"


int main(multiboot_info* info)
{  
    int numFrames;

    printWelcomeScreen();
    printRhino();

    println("press enter to start system");
    readString();
    clearScreen();

    setupIdt();
    install_gdt();
    setupIdt();
    
    
    print("\n");
    numFrames = printMultiBootInfo(info);
    println("");

    initialize_paging(numFrames);
    
    task_install();
    println("install task");
    
    //not switching to user mode becuase syscall not implemented
    //switch_to_user_mode();

    println("\npress enter");
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



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



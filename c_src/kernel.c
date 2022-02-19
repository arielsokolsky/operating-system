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
#include "../include/vfs.h"
#include "../include/ata.h"



int main(multiboot_info* info)
{  
    int numFrames;

    printWelcomeScreen();
    
    install_gdt();
    setupIdt();
    
    installFilesystem(0);
    print("\n");
    numFrames = printMultiBootInfo(info);
    println("");

    initialize_paging(numFrames);
    
    task_install();
    println("install task");
    //tss_switch();
    
    println("\npress enter");
    readString();
    clearScreen();

    runTerminal();
    

    return 0;
}


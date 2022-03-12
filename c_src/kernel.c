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
#include "../include/irq.h"
#include "../include/fs.h"


int main(multiboot_info* info)
{  
    int numFrames;
    printWelcomeScreen();
    

    printRhino();

    println("press enter to start system");
    //readString();
    clearScreen();
    
    installIrq();
    setupIdt();
    install_gdt();

    installFilesystem(0);
    
    //remove the keyboard handler(because there is already handler)
    //setIrqEnery(1, keyboard_handler);
    //irq1();

    //init_timer(100);
    
    print("\n");
    numFrames = printMultiBootInfo(info);
    println("");
    
    initialize_paging(numFrames);
    task_install();
    println("install task\n");



    // write test
    loadFs();
    
    
    string data = "this is start of a file2 ";
    string str = "this is part2";
    string stringTest = "123456789";
    string result = "", result2 = "";
    int num = 31, myResult = 0;
    uint32 myLen = sizeof(int), address = 0;

    /*
    //test: working with numbers
    address = addFragment(&num, myLen);
    
    readFragments(address, &myResult, 0);
    print("the result: ");
    printInt(myResult);
    println("");
    */
    
    address = addFragment(stringTest, strlen(stringTest));
    
    /*
    //print the fragment
    println("");
    result = 0;
    readFragments(address, result, 2, 5);
    print("the result: ");
    print(result);
    print("\n");
    */
    
    appendFragments(address, stringTest, strlen(stringTest));
    appendFragments(address, data, strlen(data));
    
    result2 = 0;
    readFragments(address, result2, 3, 8);
    print("the result2: ");
    print(result2);
    print("\n");
    /**/
    
    while(1){};    
    //end test

    //not switching to user mode becuase syscall not implemented
    //switch_to_user_mode(); 

    int working = test();
    if(working)
    {
        println("file system is ready\n");
    }
    else
    {
        println("a error accured while loading file system");
        asm("hlt");
    }
    
    println("the operating system finish initialization");
    println("press enter to start");

    readString();
    clearScreen();

    runTerminal();
    

    return 0;
}


#include "../include/headers.h"


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
    //timer isn't needed
    //init_timer(100);
    
    print("\n");
    numFrames = printMultiBootInfo(info);
    println("");
    
    initialize_paging(numFrames);
    task_install();
    println("install task\n");

    // write test
    loadFs();

    
    
    string data = "this is start of a file2 ", str = "this is part2 ";
    string result = "", result2 = "", stringTest = "123456789";
    int num = 35, myResult = 0;
    uint32 myLen = sizeof(int), address = 0;

    //create fragment
    address = addFragment(data, strlen(data));

    //print the fragment
    result = 0;
    readFragments(address, result, 0, 0);
    print("the result: ");
    print(result);
    print("\n");
    
    //add to fragment
    appendFragments(address, str, strlen(str));

    //insert stringTest before str
    pushFragments(address, stringTest, strlen(stringTest));
    //appendFragments(address, stringTest, strlen(stringTest));
    


    uint32 findAddress = findFragment(address, 22);
    //read fragment again
    result2 = 0;
    readFragments(findAddress, result2, 0, 0);
    print("the result: ");
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


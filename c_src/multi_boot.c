#include "../include/types.h"
#include "../include/screen.h"
#include "../include/multi_boot.h"

/*
the function gets the multiboot information and it prints it
param: information about the computer from the multiboot
return: the amounts of frames in the system
*/
int printMultiBootInfo(multiboot_info* info)
{
    int total_frames = 0;
    println("print multi boot info: ");

    println(info->u.aout_sym_t.tab_size ? "your using out format" : "your using elf format");
    
    total_frames = 256 + (info->mem_upper * 1024 / 4096);
    print("total frames: ");
    printInt(total_frames);

    return total_frames;
}
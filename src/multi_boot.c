#include "../include/types.h"
#include "../include/screen.h"
#include "../include/multi_boot.h"

int printMultiBootInfo(multiboot_info* info)
{
    int total_frame = 256 + (info->mem_upper * 1024 / 4096);
    println("print multi boot info: ");

    println(info->u.aout_sym_t.tab_size ? "your using out format" : "your using elf format");
    

    print("total frames: ");
    printInt(total_frame);

    print("\npress enter");
    return total_frame;
}
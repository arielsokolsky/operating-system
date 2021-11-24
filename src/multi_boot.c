#include "../include/types.h"
#include "../include/screen.h"
#include "../include/multi_boot.h"

void printMultiBootInfo(multiboot_info* info)
{
    int i;
    print("print multi boot info: \n");

    print(info->u.aout_sym_t.tab_size ? "your using out format" : "your using elf format");
    print("\n");
    
    print("lower : ");
    printInt(info->mem_lower);
    print(" upper : ");
    printInt(info->mem_upper);
    print(" len : ");
    printInt(info->mmap_length);
    print(" add : ");
    printInt(info->mmap_addr);
    print(" mode : ");
    printInt(info->mods_addr);
    print(" flags : ");
    printInt(info->flags);

    for(i = 0; i < info->mmap_length; i += sizeof(multiboot_memory_map_t)) 
    {
        multiboot_memory_map_t* mmmt = (multiboot_memory_map_t*) (info->mmap_addr + i);

        print("Start Addr: ");
        printInt(i);//mmmt->addr);
        //printf("Start Addr: %x | Length: %x | Size: %x | Type: %d\n",mmmt->addr_low, mmmt->len_low, mmmt->size, mmmt->type);
 
        if(mmmt->type == MULTIBOOT_MEMORY_AVAILABLE) 
        {
            /* 
             * Do something with this memory block!
             * BE WARNED that some of memory shown as availiable is actually 
             * actively being used by the kernel! You'll need to take that
             * into account before writing to memory!
             */
        }
    }
    
}
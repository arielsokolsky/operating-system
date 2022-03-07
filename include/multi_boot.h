#ifndef MULTI_BOOT_H
#define MULTI_BOOT_H
#include "types.h"

//! The symbol table for a.out format.
typedef struct aout_symbol_table_t{
      uint32 tab_size;
      uint32 str_size;
      uint32 address;
      uint32 reserved;
} aout_symbol_table_t;

//! The section header table for ELF format.
typedef struct elf_section_header_table_t{
      uint32 num;
      uint32 size;
      uint32 address;
      uint32 shndx;
} elf_section_header_table_t;

typedef struct multiboot_info
{
    uint32 flags;
    uint32 mem_lower;
    uint32 mem_upper;
    uint32 boot_device;
    uint32 cmdline;
    uint32 mods_addr;
    union
    {
        aout_symbol_table_t aout_sym_t;
        elf_section_header_table_t elf_sec_t;
    } u;
    uint32 mmap_length;
    uint32 mmap_addr;
}multiboot_info;

typedef struct multiboot_memory_map
{
	uint8 size;
	uint64 base_addr;
	uint64 length;
	uint8 type;
} multiboot_memory_map;

int printMultiBootInfo(multiboot_info*);

#endif


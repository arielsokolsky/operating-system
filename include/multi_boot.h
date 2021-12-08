#ifndef MULTI_BOOT_H
#define MULTI_BOOT_H
#include "types.h"

//! The symbol table for a.out format.
typedef struct aout_symbol_table_t{
      unsigned_int32 tab_size;
      unsigned_int32 str_size;
      unsigned_int32 address;
      unsigned_int32 reserved;
} aout_symbol_table_t;

//! The section header table for ELF format.
typedef struct elf_section_header_table_t{
      unsigned_int32 num;
      unsigned_int32 size;
      unsigned_int32 address;
      unsigned_int32 shndx;
} elf_section_header_table_t;

typedef struct multiboot_info
{
    unsigned_int32 flags;
    unsigned_int32 mem_lower;
    unsigned_int32 mem_upper;
    unsigned_int32 boot_device;
    unsigned_int32 cmdline;
    unsigned_int32 mods_addr;
    union
    {
        aout_symbol_table_t aout_sym_t;
        elf_section_header_table_t elf_sec_t;
    } u;
    unsigned_int32 mmap_length;
    unsigned_int32 mmap_addr;
}multiboot_info;


struct multiboot_mmap_entry
{
  unsigned_int32 size;
  unsigned_int32 addr_low;
  unsigned_int32 addr_high;
  unsigned_int32 len_low;
  unsigned_int32 len_high;
#define MULTIBOOT_MEMORY_AVAILABLE              1
#define MULTIBOOT_MEMORY_RESERVED               2
#define MULTIBOOT_MEMORY_ACPI_RECLAIMABLE       3
#define MULTIBOOT_MEMORY_NVS                    4
#define MULTIBOOT_MEMORY_BADRAM                 5
  unsigned_int32 type;
} __attribute__((packed));
typedef struct multiboot_mmap_entry multiboot_memory_map_t;

int printMultiBootInfo(multiboot_info*);

#endif


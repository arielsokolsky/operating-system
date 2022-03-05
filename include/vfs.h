#include "string.h"
#include "malloc.h"

struct bios_parameter_block {
    uint16 bytes_per_sector;          // IMPORTANT
    uint8 sectors_per_cluster;        // IMPORTANT
    uint16 reserved_sectors;          // IMPORTANT
    uint8 FAT_count;                  // IMPORTANT
    uint16 dir_entries;
    uint16 total_sectors;
    uint8 media_descriptor_type;
    uint16 count_sectors_per_FAT12_16; // FAT12/FAT16 only.
    uint16 count_sectors_per_track;
    uint16 count_heads_or_sizes_on_media;
    uint32 count_hidden_sectors;
    uint32 large_sectors_on_media;  // This is set instead of total_sectors if it's > 65535

    // Extended Boot Record
    uint32 count_sectors_per_FAT32;   // IMPORTANT
    uint16 flags;
    uint16 FAT_version;
    uint32 cluster_number_root_dir;   // IMPORTANT
    uint16 sector_number_FSInfo;
    uint16 sector_number_backup_boot_sector;
    uint8 drive_number;
    uint8 windows_flags;
    uint8 signature;                  // IMPORTANT
    uint32 volume_id;
    char volume_label[12];
    char system_id[9];
};

struct dir_entry {
    char *name;
    uint8 dir_attrs;
    uint32 first_cluster;
    uint32 file_size;
};

struct directory {
    uint32 cluster;
    struct dir_entry *entries;
    uint32 num_entries;
};

typedef struct fat32 {
    //FILE *f;
    uint32 *FAT;
    uint32 partition_begin_sector;
    uint32 fat_begin_sector;
    struct bios_parameter_block bpb;
    uint32 cluster_sector_begin;
    uint32 cluster_size;
    uint32 cluster_alloc_hint;
}fat32;



fat32 *installFilesystem(char *fatSystem);

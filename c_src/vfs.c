#include "../include/vfs.h"
#include "../include/ata_pio_drv.h"
#include "../include/screen.h"

static void trim_spaces(char *c, int max) {
    int i = 0;
    while(*c != ' ' && i++ < max) {
        c++;
    }
    if(*c == ' ') *c = 0;
}
//transforms 2 8-bit parameter into 1 16-bit parameter
static uint16 readi16(uint8 *buff, uint32 offset)
{
    uint8 *ubuff = buff + offset;
    return ubuff[1] << 8 | ubuff[0];
}

//transforms 4 8-bit parameter into 1 32-bit parameter
static uint32 readi32(uint8 *buff, uint32 offset) {
    uint8 *ubuff = buff + offset;
    return
        ((ubuff[3] << 24) & 0xFF000000) |
        ((ubuff[2] << 16) & 0x00FF0000) |
        ((ubuff[1] << 8) & 0x0000FF00) |
        (ubuff[0] & 0x000000FF);
}

static uint32 sector_for_cluster(fat32 *fs, uint32 cluster) {
    return fs->cluster_sector_begin + ((cluster - 2) * fs->bpb.sectors_per_cluster);
}

static void read_bpb(fat32 *fs, struct bios_parameter_block *bpb) 
{
    uint8 sector0[512];
    ata_pio_read48(sector0, 0, 1);

    bpb->bytes_per_sector = readi16(sector0, 11);;
    bpb->sectors_per_cluster = sector0[13];
    bpb->reserved_sectors = readi16(sector0, 14);
    bpb->FAT_count = sector0[16];
    bpb->dir_entries = readi16(sector0, 17);
    bpb->total_sectors = readi16(sector0, 19);
    bpb->media_descriptor_type = sector0[21];
    bpb->count_sectors_per_FAT12_16 = readi16(sector0, 22);
    bpb->count_sectors_per_track = readi16(sector0, 24);
    bpb->count_heads_or_sizes_on_media = readi16(sector0, 26);
    bpb->count_hidden_sectors = readi32(sector0, 28);
    bpb->large_sectors_on_media = readi32(sector0, 32);
    // EBR
    bpb->count_sectors_per_FAT32 = readi32(sector0, 36);
    bpb->flags = readi16(sector0, 40);
    bpb->FAT_version = readi16(sector0, 42);
    bpb->cluster_number_root_dir = readi32(sector0, 44);
    bpb->sector_number_FSInfo = readi16(sector0, 48);
    bpb->sector_number_backup_boot_sector = readi16(sector0, 50);
    // Skip 12 bytes
    bpb->drive_number = sector0[64];
    bpb->windows_flags = sector0[65];
    bpb->signature = sector0[66];
    bpb->volume_id = readi32(sector0, 67);
    memcpy(&bpb->volume_label, sector0 + 71, 11); bpb->volume_label[11] = 0;
    memcpy(&bpb->system_id, sector0 + 82, 8); bpb->system_id[8] = 0;
}

fat32 *installFilesystem(char *fatSystem)
{
    fat32 *fs = malloc(sizeof (fat32));
    if (!identify())
    {
        print("not exist");
        return 0;
    }
    //read the bios parameter block from the memory
    read_bpb(fs, &fs->bpb);
    
    //sets all the sectors and parameters using information from the bios
    fs->partition_begin_sector = 0;
    fs->fat_begin_sector = fs->bpb.reserved_sectors;
    fs->cluster_alloc_hint = 0;
    fs->cluster_size = 512 * fs->bpb.sectors_per_cluster;
    fs->cluster_sector_begin = fs->bpb.FAT_count * fs->bpb.count_sectors_per_FAT32;

    //mallocs the FAT into the memory
    fs->FAT = malloc(fs->bpb.count_sectors_per_FAT32 * 512);
    // read from the memory every sector and put it inthe right place until the FAT is contains 
    // all the file system that is in the memory
    uint32 i, j, sector[512];
    for (i = 0; i < fs->bpb.count_sectors_per_FAT32; i++)
    {
        ata_pio_read48(sector, fs->fat_begin_sector + i, 1);
        for (j = 0; j < 128; j++)
        {
            fs->FAT[i * 128 + j] = readi32(sector, j * 4);
        }
    }

    return fs;

}

void getSector(fat32* fs, uint8 *buffer, uint32 cluster_num)
{
    uint32 sector = sector_for_cluster(fs, cluster_num);
    ata_pio_write48(sector, fs->bpb.sectors_per_cluster ,buffer);
}
//reads each correct parameter from the bios in the memory and puts it in the memory

uint8 *readFile(fat32 *fs, struct dir_entry *dirent) {
    uint8 *file = kmalloc(dirent->file_size);
    uint8 *filecurrptr = file;
    uint32 cluster = dirent->first_cluster;
    uint32 copiedbytes = 0;
    while(1) {
        uint8 cbytes[fs->cluster_size];
        getCluster(fs, cbytes, cluster);

        uint32 remaining = dirent->file_size - copiedbytes, to_copy;
        if (remaining > fs->cluster_size)
        {
            to_copy = fs->cluster_size;
        }
        else{
            to_copy = remaining;
        }


        memcpy(filecurrptr, cbytes, to_copy);

        filecurrptr += fs->cluster_size;
        copiedbytes += to_copy;

        cluster = fs->FAT[cluster] & 0x0FFFFFFF;
        if(cluster >= EOC) break;
    }
    return file;
}
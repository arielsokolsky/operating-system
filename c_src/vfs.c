#include "../include/vfs.h"
#include "../include/ata_pio_drv.h"


fat32 *installFilesystem(char *fatSystem)
{
    fat32 *fs = malloc(sizeof (fat32));
    if (!identify())
    {
        return 0;
    }

    read_bpb(fs, &fs->bpb);
    



    

}

static void trim_spaces(char *c, int max) {
    int i = 0;
    while(*c != ' ' && i++ < max) {
        c++;
    }
    if(*c == ' ') *c = 0;
}
static uint16 readi16(uint8 *buff, uint32 offset)
{
    uint8 *ubuff = buff + offset;
    return ubuff[1] << 8 | ubuff[0];
}

static uint32 readi32(uint8 *buff, uint32 offset) {
    uint8 *ubuff = buff + offset;
    return
        ((ubuff[3] << 24) & 0xFF000000) |
        ((ubuff[2] << 16) & 0x00FF0000) |
        ((ubuff[1] << 8) & 0x0000FF00) |
        (ubuff[0] & 0x000000FF);
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
#ifndef ATA_H 
#define ATA_H

#include "types.h"
#include "system.h"

void read_sectors_ATA_PIO(uint32 target_address, uint32 LBA, uint8 sector_count);
void write_sectors_ATA_PIO(uint32 LBA, uint8 sector_count, uint32* bytes);


#endif

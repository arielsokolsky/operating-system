#ifndef ATA_PIO_DRV_H
#define ATA_PIO_DRV_H
#include "types.h"


uint8 identify();
void ata_pio_write48(uint32 LBA, uint8 sectorcount, uint8 *target);
void ata_pio_read48(uint32 LBA, uint8 sectorcount, uint8 *target);

#endif
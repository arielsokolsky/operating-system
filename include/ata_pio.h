#ifndef ATA_PIO_H 
#define ATA_PIO_H

#include "types.h"
#include "system.h"

#define MAGIC_NUMBER 0X2

#define ATA_PRIMARY_DATA         0x1F0
#define ATA_PRIMARY_ERR          0x1F1
#define ATA_PRIMARY_SECCOUNT     0x1F2
#define ATA_PRIMARY_LBA_LO       0x1F3
#define ATA_PRIMARY_LBA_MID      0x1F4
#define ATA_PRIMARY_LBA_HI       0x1F5
#define ATA_PRIMARY_DRIVE_HEAD   0x1F6
#define ATA_PRIMARY_COMM_REGSTAT 0x1F7
#define ATA_PRIMARY_ALTSTAT_DCR  0x3F6


#define STAT_ERR  (1 << 0) // Indicates an error occurred. Send a new command to clear it
#define STAT_DRQ  (1 << 3) // Set when the drive has PIO data to transfer, or is ready to accept PIO data.
#define STAT_SRV  (1 << 4) // Overlapped Mode Service Request.
#define STAT_DF   (1 << 5) // Drive Fault Error (does not set ERR).
#define STAT_RDY  (1 << 6) // Bit is clear when drive is spun down, or after an error. Set otherwise.
#define STAT_BSY  (1 << 7) // Indicates the drive is preparing to send/receive data (wait for it to clear).


void read_sectors_ATA_PIO(uint32 target_address, uint32 LBA, uint8 sector_count);
void write_sectors_ATA_PIO(uint32 LBA, uint8 sector_count, uint32* bytes);
uint8 identify_pio();
bool test_pio();

#endif

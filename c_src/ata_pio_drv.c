#include "../include/ata_pio_drv.h"
#include "../include/system.h"

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
                           // In case of 'hang' (it never clears), do a software reset.

uint8 identify() {
    inputPort(ATA_PRIMARY_COMM_REGSTAT);
    outportb(ATA_PRIMARY_DRIVE_HEAD, 0xA0);
    inputPort(ATA_PRIMARY_COMM_REGSTAT);
    outportb(ATA_PRIMARY_SECCOUNT, 0);
    inputPort(ATA_PRIMARY_COMM_REGSTAT);
    outportb(ATA_PRIMARY_LBA_LO, 0);
    inputPort(ATA_PRIMARY_COMM_REGSTAT);
    outportb(ATA_PRIMARY_LBA_MID, 0);
    inputPort(ATA_PRIMARY_COMM_REGSTAT);
    outportb(ATA_PRIMARY_LBA_HI, 0);
    inputPort(ATA_PRIMARY_COMM_REGSTAT);
    outportb(ATA_PRIMARY_COMM_REGSTAT, 0xEC);
    outportb(ATA_PRIMARY_COMM_REGSTAT, 0xE7);

    // Read the status port. If it's zero, the drive does not exist.
    uint8 status = inb(ATA_PRIMARY_COMM_REGSTAT);

    printf("Waiting for status.\n");
    while(status & STAT_BSY) {
        uint32 i = 0;
        while(1) {
            printf("Printing stuff %d\n", i);
            i++;
        }
        for(i = 0; i < 0x0FFFFFFF; i++) {}
        printf("Checking regstat.\n");
        status = inputPort(ATA_PRIMARY_COMM_REGSTAT);
    }
    
    if(status == 0) return 0;

    printf("Status indicates presence of a drive. Polling while STAT_BSY... ");
    while(status & STAT_BSY) {
      printf("\ninb(ATA_PRIMARY_COMM_REGSTAT);... ");
      status = inputPort(ATA_PRIMARY_COMM_REGSTAT);
    }
    printf("Done.\n");

    uint8 mid = inputPort(ATA_PRIMARY_LBA_MID);
    uint8 hi = inputPort(ATA_PRIMARY_LBA_HI);
    if(mid || hi) {
        // The drive is not ATA. (Who knows what it is.)
        return 0;
    }

    printf("Waiting for ERR or DRQ.\n");
    // Wait for ERR or DRQ
    while(!(status & (STAT_ERR | STAT_DRQ))) {
        status = inputPort(ATA_PRIMARY_COMM_REGSTAT);
    }

    if(status & STAT_ERR) {
        // There was an error on the drive. Forget about it.
        return 0;
    }

    printf("Reading IDENTIFY structure.\n");
    //uint8_t *buff = kmalloc(40960, 0, NULL);
    uint8 buff[256 * 2];
    insw(ATA_PRIMARY_DATA, buff, 256);
    printf("Success. Disk is ready to go.\n");
    // We read it!
    return 1;
}

void ata_pio_write48(uint64 LBA, uint16 sectorcount, uint8 *target) {

    // HARD CODE MASTER (for now)
    outportb(ATA_PRIMARY_DRIVE_HEAD, 0x40);                     // Select master
    outportb(ATA_PRIMARY_SECCOUNT, (sectorcount >> 8) & 0xFF ); // sectorcount high
    outportb(ATA_PRIMARY_LBA_LO, (LBA >> 24) & 0xFF);           // LBA4
    outportb(ATA_PRIMARY_LBA_MID, (LBA >> 32) & 0xFF);          // LBA5
    outportb(ATA_PRIMARY_LBA_HI, (LBA >> 40) & 0xFF);           // LBA6
    outportb(ATA_PRIMARY_SECCOUNT, sectorcount & 0xFF);         // sectorcount low
    outportb(ATA_PRIMARY_LBA_LO, LBA & 0xFF);                   // LBA1
    outportb(ATA_PRIMARY_LBA_MID, (LBA >> 8) & 0xFF);           // LBA2
    outportb(ATA_PRIMARY_LBA_HI, (LBA >> 16) & 0xFF);           // LBA3
    outportb(ATA_PRIMARY_COMM_REGSTAT, 0x34);                   // READ SECTORS EXT

    uint8 i;
    for(i = 0; i < sectorcount; i++) {
        // POLL!
        while(1) {
            uint8 status = inputPort(ATA_PRIMARY_COMM_REGSTAT);
            if(status & STAT_DRQ) {
                // Drive is ready to transfer data!
                break;
            }
            
        }
        // Transfer the data!
        outsw(ATA_PRIMARY_DATA, (void *)target, 256);
        target += 256;
    }

    // Flush the cache.
    outportb(ATA_PRIMARY_COMM_REGSTAT, 0xE7);
    // Poll for BSY.
    while(inputPort(ATA_PRIMARY_COMM_REGSTAT) & STAT_BSY) {}
}
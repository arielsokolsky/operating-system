#include "../include/ata.h"




char* read(uint32 LBA, uint8 sector_count)
{
    char bwrite[512];
    uint32* target;
    //reading again
    readBasic(target, LBA, sector_count);
	
    int i = 0;
    int num = 0;
    while(i < 128)
    {
        for(int j = 0; j < 4; j++)
        {
            num = (target[i] >> (8 * j)) & 0xFF;
            char a = (char) num;
            bwrite[j] = a;
        }
        i++;
    }
    return bwrite;
}


void readBasic(uint32 target_address, uint32 LBA, uint8 sector_count)
{
	ATA_wait_BSY();
	outPort(0x1F6,0xE0 | ((LBA >>24) & 0xF));
	outPort(0x1F2,sector_count);
	outPort(0x1F3, (uint8) LBA);
	outPort(0x1F4, (uint8)(LBA >> 8));
	outPort(0x1F5, (uint8)(LBA >> 16)); 
	outPort(0x1F7,0x20); //Send the read command
	
	uint16 *target = (uint16*) target_address;
	
	for (int j =0; j < sector_count ;j++)
	{
		ATA_wait_BSY();
		ATA_wait_DRQ();
		for(int i=0;i<256;i++)
		{
			target[i] = inputPortWord(0x1F0);
		}	
		target+=256;
	}
    

}

void writeBasic(uint32 LBA, uint8 sector_count, uint32* bytes)
{
	ATA_wait_BSY();
	outPort(0x1F6,0xE0 | ((LBA >>24) & 0xF));
	outPort(0x1F2,sector_count);
	outPort(0x1F3, (uint8) LBA);
	outPort(0x1F4, (uint8)(LBA >> 8));
	outPort(0x1F5, (uint8)(LBA >> 16)); 
	outPort(0x1F7,0x30); //Send the write command

	for (int j =0;j<sector_count;j++)
	{
		ATA_wait_BSY();
		ATA_wait_DRQ();
		for(int i=0;i<256;i++)
		{
			outPortDword(0x1F0, bytes[i]);
		}
	}
}

static void ATA_wait_BSY()   //Wait for bsy to be 0
{
	while(inputPort(0x1F7)&STATUS_BSY);
}
static void ATA_wait_DRQ()  //Wait fot drq to be 1
{
	while(!(inputPort(0x1F7)&STATUS_RDY));
}


bool test()
{
	bool working = true;
	int i = 0;

	uint32* target;

    //writing 0
    char bwrite[512];
    for(i = 0; i < 512; i++)
    {
        bwrite[i] = '1';
    }
    bwrite[0] = 'a';
    bwrite[1] = 'r';
    bwrite[2] = 'i';
    bwrite[3] = 'e';
    bwrite[80] = 'g';
    writeBasic(0x0, 1, bwrite);

	char* buffer = read(0x0, 1);
    for (int i = 0; i < 512; i++)
    {
        printch(buffer[i]);
    }

    return working; 
}


uint8 identify() 
{
    //puts 0 on the sector count and in the linear block address
    inputPort(ATA_PRIMARY_COMM_REGSTAT);
    outPort(ATA_PRIMARY_DRIVE_HEAD, 0xA0);
    inputPort(ATA_PRIMARY_COMM_REGSTAT);
    outPort(ATA_PRIMARY_SECCOUNT, 0);
    inputPort(ATA_PRIMARY_COMM_REGSTAT);
    outPort(ATA_PRIMARY_LBA_LO, 0);
    inputPort(ATA_PRIMARY_COMM_REGSTAT);
    outPort(ATA_PRIMARY_LBA_MID, 0);
    inputPort(ATA_PRIMARY_COMM_REGSTAT);
    outPort(ATA_PRIMARY_LBA_HI, 0);
    //run command 0xE7 in the command registat port address
    inputPort(ATA_PRIMARY_COMM_REGSTAT);
    outPort(ATA_PRIMARY_COMM_REGSTAT, 0xEC);
    outPort(ATA_PRIMARY_COMM_REGSTAT, 0xE7);

    // Read the status port. If it's zero, the drive does not exist.
    uint8 status = inputPort(ATA_PRIMARY_COMM_REGSTAT);

    //wait as long as the bsy is still active
    while(status & STAT_BSY) {
        uint32 i = 0;
        
        for(i = 0; i < 0x0FFFFFFF; i++) {}
        status = inputPort(ATA_PRIMARY_COMM_REGSTAT);
    }
    
    if(status == 0) return 0;

    //printf("Status indicates presence of a drive. Polling while STAT_BSY... ");
    while(status & STAT_BSY) {
      //printf("\ninb(ATA_PRIMARY_COMM_REGSTAT);... ");
      status = inputPort(ATA_PRIMARY_COMM_REGSTAT);
    }
    //printf("Done.\n");

    uint8 mid = inputPort(ATA_PRIMARY_LBA_MID);
    uint8 hi = inputPort(ATA_PRIMARY_LBA_HI);
    if(mid || hi) {
        // The drive is not ATA. (Who knows what it is.)
        return 0;
    }

    //printf("Waiting for ERR or DRQ.\n");
    // Wait for ERR or DRQ
    while(!(status & (STAT_ERR | STAT_DRQ))) {
        status = inputPort(ATA_PRIMARY_COMM_REGSTAT);
    }

    if(status & STAT_ERR) {
        // There was an error on the drive. Forget about it.
        return 0;
    }

    //printf("Reading IDENTIFY structure.\n");
    //uint8_t *buff = kmalloc(40960, 0, NULL);
    uint8 buff[552];
    insw(ATA_PRIMARY_DATA, buff, 256);
    //printf("Success. Disk is ready to go.\n");
    // We read it!
    return 1;
}


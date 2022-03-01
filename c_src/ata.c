#include "../include/ata.h"


/*
the function first write all the full sector and to write the what left she read change the data and write again
param LBA: the address to where to write
param len: how byte to write
param byte: what to write
return: none
*/
void write(uint32 address, uint32 len, void* bytes)
{
    uint8* data = (uint8 *)bytes;
    int startSector = address / SECTOR_SIZE;
    int numOfSectors = len / SECTOR_SIZE;
    int lastSector = startSector + numOfSectors;
    int lastSectorLen = len % SECTOR_SIZE;

    //write the full sectors
    if(numOfSectors > 0)
    {
        writeBasic(startSector, numOfSectors, data);
    }
    
    //read the data of the last sector
    char buffer[512];
    readBasic(buffer, lastSector, 1);
    
    //change part of the data
    for (int i = 0; i < lastSectorLen; i++)
    {
        buffer[i] = data[numOfSectors * SECTOR_SIZE + i];
    }
    
    //send the same data with changes
    if(lastSectorLen > 0)
    {
        writeBasic(lastSector, 1, buffer);
    }
}

void readBasic(void* target_address, uint32 LBA, uint8 sector_count)
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
    string str = "12345";
    char bwrite[600] = {0};
    
    strcpy(bwrite, str);

    for(int i = 0; i < 600; i++)
    {
        bwrite[i] = str[i % 5];
    }

    for(int i = 512; i < 600; i++)
    {
        bwrite[i] = 'a';
    }
    write(0x0, 550, bwrite);

    char buffer[1024];
    readBasic(buffer, 0x0, 2);

    for (int i = 0; i < 550; i++)
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

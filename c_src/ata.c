#include "../include/ata.h"


/*
the function can write to any address with any length
param address: the address to where to write
param len: how many byte to write
param byte: what to write
return: none
*/
void write(uint32 address, uint32 len, void* bytes)
{
    uint8* data = (uint8 *)bytes;
    char buffer[512];
    int currentLocation = 0;

    int startSector = address / SECTOR_SIZE;
    int startSectorAddr = address % SECTOR_SIZE;
    int lenFirstSector = SECTOR_SIZE - (address % SECTOR_SIZE);

    int finalSector = (address + len) / SECTOR_SIZE;

    // the minos 1 is exclude the first sector
    int fullSectorCount = finalSector - startSector - 1;

    //start + middle + end = len => end = len - start - middle
    int finalSectorLen = len - lenFirstSector - fullSectorCount * SECTOR_SIZE;

    //check if more then one sector
    if(lenFirstSector > len)
    {
        lenFirstSector = len;
    }

    //read the first sector
    readBasic(buffer, startSector, 1);
    //change first sector
    for (currentLocation = 0; currentLocation < lenFirstSector; currentLocation++)
    {
        buffer[startSectorAddr + currentLocation] = data[currentLocation];
    }
    //write it 
    writeBasic(startSector, 1, buffer);

    
    //write the full sectors
    if(fullSectorCount > 0)
    {
        writeBasic(startSector + 1, fullSectorCount, data + currentLocation);
        currentLocation += fullSectorCount * SECTOR_SIZE;
    }
    
    //check if last sector exist
    if(finalSectorLen == 0)
    {
        return;
    }

    //read the data of the last sector
    readBasic(buffer, finalSector, 1);
    
    //change part of the data
    for (int i = 0; i + currentLocation < len; i++)
    {
        buffer[i] = data[currentLocation + i];
    }
    
    //send the same data with changes
    writeBasic(finalSector, 1, buffer);
    
    return;
}

/*
the function can read from any address with any length
param buffer: where to to store the data
param len: how many byte to write
param address: what address to read from
return: none
*/
void read(void* buffer, uint32 address, uint32 len)
{
    int currentLocation = 0;
    uint8* bytes = (uint8*) buffer;
    char data[512] = {0};
    int lenFirstSector = SECTOR_SIZE - (address % SECTOR_SIZE);
    int startSector = address / SECTOR_SIZE;
    int finalSector = (address + len) / SECTOR_SIZE;
    int FullSectorCount = finalSector - startSector - 1;
    
    if(lenFirstSector > len)
    {
        lenFirstSector = len;
    }

    //read the first sector
    readBasic(data, startSector, 1);
    for (currentLocation = 0; currentLocation < lenFirstSector; currentLocation++)
    {
        bytes[currentLocation] = data[(address % SECTOR_SIZE) + currentLocation];
    }
    
    //read all the full sector
    if(FullSectorCount > 0)
    {
        readBasic(buffer + currentLocation, startSector + 1, FullSectorCount);
        currentLocation += FullSectorCount * SECTOR_SIZE;
    }


    //read the final sector
    if(currentLocation - len != 0)
    {
        readBasic(data, finalSector, 1);
        for (int i = 0; i < len - currentLocation; i++)
        {
            bytes[currentLocation + i] = data[i];
        }
    }
}

/*
the function can read from a sepecific sector and can only read sector size
param target_address: where to store the data
param lba: the sector number to read from
param sector_count : how many sectors to read
return: none
*/
void readBasic(void* target_address, uint32 LBA, uint8 sector_count)
{
    if(sector_count == 0)
    {
        return;
    }
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

/*
the function can write to a sepecific sector and can only write sector size
param bytes: what data to write
param lba: the sector number to read from
param sector_count : how many sectors to read
return: none
*/
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

/*
the function check that read and write working
param: none
return: if working return true else return false
*/
bool test()
{
	bool working = true;
    char bwrite[50] = {0};
    char buffer[50] = {0};
	int i = 0;

	uint32* target;
    string str = "hello this is test";
    int len = strlen(str);
    
    strcpy(bwrite, str);

    write(500, len, bwrite);
    
    read(buffer, 500, len);

    working = strcmp(buffer, bwrite);

    return working; 
}

/*
the function check if disk connected
param: none
return: if file exist return 1 else 0
*/
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

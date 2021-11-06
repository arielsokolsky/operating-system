ENTRY(start)

SECTIONS
{
    . = 1M;

    .multiboot : { *(.multiboot) }
    .text : { *(.text) }
    .boot.bss ALIGN(0x1000) : 
    {
		*(.bss)
	}

}
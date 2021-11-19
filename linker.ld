ENTRY(start)

SECTIONS
{
    . = 1M;

    .multiboot : { *(.multiboot) }
    .text : { *(.text) }
    .bss ALIGN(0x1000) : {*(.bss)}

}
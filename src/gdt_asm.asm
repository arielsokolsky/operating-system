extern gp
global _gdt_flush     ; Allows the C code to link to this
           ; Says that 'gp' is in another file
_gdt_flush:
    lgdt [gp]        ; Load the GDT with our '_gp' which is a special pointer
    ret  
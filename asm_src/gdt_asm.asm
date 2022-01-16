extern gp
[GLOBAL tss_flush]
global _gdt_flush     
           
_gdt_flush:
    lgdt [gp]        
    ret  

tss_flush:
    mov ax, 0x2B
    ltr ax
    ret
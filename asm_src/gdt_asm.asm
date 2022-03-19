extern gp
global _gdt_flush     
           
_gdt_flush:
    lgdt [gp]        
    ret  


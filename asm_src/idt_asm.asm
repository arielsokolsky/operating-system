;load the table into the processer
global idt_load
extern _lidt
idt_load:
    lidt [_lidt]
    ret
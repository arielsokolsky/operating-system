;load the table into the processer
extern _lidt
global installIdt

installIdt:
    lidt[_lidt]
    ret
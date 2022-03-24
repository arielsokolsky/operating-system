#ifndef SHELL_H
#define SHELL_H
#include "screen.h"
#include "input.h"
#include "calculator.h"

extern uint32 isCommand;

void runTerminal();
void help();
void printColors();

#endif
#ifndef INPUT_H
#define INPUT_H

#include "screen.h"
#include "system.h"
#include "malloc.h"

#define CHECK_PORT 0x64
#define READ_PORT 0x60
#define MAX_BUFFER_SIZE 200




string readString();
void deleteCommand(int len);
void changeCommand(string* newCommand, int len);


#endif
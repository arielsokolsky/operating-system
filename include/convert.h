#ifndef CONVERT_H
#define CONVERT_H

#include "types.h"

string intToString(int num);
int stringToInt(string str);
void* memset(void* dst, int value, int unsigned len);
void* memcpy(const void* src, void* dst, int unsigned len);

#endif
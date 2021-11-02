#ifndef TYPES_H
#define TYPES_H

typedef signed char int8;
typedef signed short int16;
typedef signed int int32;
typedef signed long long int64;

typedef unsigned char unsigned_int8;
typedef unsigned short unsigned_int16;
typedef unsigned int unsigned_int32;
typedef unsigned long long unsigned_int64;

typedef _Bool bool;
#define false 0
#define true !(false)

typedef char* string;

#define low_16(address) (uint16)((address) & 0xFFFF)            
#define high_16(address) (uint16)(((address) >> 16) & 0xFFFF)

#endif
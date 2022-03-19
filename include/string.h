#ifndef STRING_H
#define STRING_H
#include "./types.h"

//the function copy str src to str dst
void strcpy(string dest, string source);

//return the length of a string
int strlen(string str);

//return if string the same
_Bool strcmp(string str1, string str2);

//reverse the string
string strrev(string str);

#endif
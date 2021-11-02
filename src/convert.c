#include "../include/system.h"
#include "../include/screen.h"

int stringToInt(string str)
{
   int i = 0, sum = 0;
   while(str[i]!='\0')
   {
      if(str[i]< 48 || str[i] > 57)
      {
        print("cannot convert string to int\n");
        return 0;
      }
      else
      {
        sum = sum*10 + (str[i] - 48);
        i++;
      }
   }
   return sum;
}
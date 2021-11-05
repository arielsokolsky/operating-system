#include "../include/system.h"
#include "../include/screen.h"

/*
the function convert string to int
param: the string
return: the string as int
*/
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

/*
the function convert int to string
param: the number
return: the number as string
*/
string intToString(int num)
{
	string str;
	int count = 0;

	do
	{
		str[count] = (num % 10) | '0' ;
		num /= 10;
		count++;
	} while (num > 0);
	
	str[count] = 0;

	return strrev(str);
}

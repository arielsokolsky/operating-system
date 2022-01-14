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
	bool nagtive = false;
	if (str[0] == '-')
	{
		nagtive = true;
		i++;
	}
	
	while(str[i])
	{
		//check that letter can be convert to int 
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
	
	//if number negative 
	if(nagtive)
	{
		sum = sum * -1;
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
	char str[20];

	int count = 0;
	bool nagtive = false;

	//check if number nagtive
	if (num < 0 )
	{
		num *= -1;
		nagtive = true;
	}
	
	do
	{	
		str[count] = (num % 10) | '0' ;
		num /= 10;
		count++;
	} while (num != 0);
	
	//if negative add '-'
	if (nagtive)
	{
		str[count] = '-';
		count++;
	}
	
	str[count] = 0;

	return strrev(str);
}

/*
the function set a section to var
dst: address to change
value: the value to change to
len: what length to change
ret: the address that was changed
*/
void* memset(void* dst, int value, int unsigned len)
{
    int unsigned i = 0;
    for ( i = 0; i < len; i++)
    {
        ((int*)dst)[i] = value;
    }
    return dst;
}

/*
the function copy memory
src: the src memory
dst: the destion memory
len: how much to copy
ret: destion address 
*/
void* memcpy(const void* src, void* dst, int unsigned len)
{
	readString();
    for (unsigned int i = 0; i < len; i++)
    {
        ((int*)dst)[i] = ((int*)src)[i];
    }
    return dst;
}

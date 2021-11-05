#include "../include/calculator.h"

/*
the function get a nubmer(x) and reutrn the number entery x in fibonacci serious
param: entery number
return: the number in the entery
*/
int fibonacci(int num)
{
    if(num <= 1)
    {
        return num;
    }
    return fibonacci(num - 1) + fibonacci(num - 2);
}

/*
the function sort array of ints
param: the array
return: none(the param change because he is pointer)
*/
void sort(int* array, int len)
{
    int temp = 0;
    
    for(int i = 0; i < len; i++)
    {
        for(int j = 0; j < len; j++)
        {
            if(array[i] < array[j])
            {
                temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }

    return array;
}
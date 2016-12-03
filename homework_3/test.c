#include<stdio.h>
#include<stdlib.h>
#define SIZE 50


int isNumber(char symbol)
{
    if ('0' <= symbol && symbol <= '9')
    {
        return 1;
    }
    return 0;
}


int getInt(char c)
{
    return (int)(c - '0');
}


int main()
{
    //printf("%d", getInt('6'));
    int** a = (int**) malloc(sizeof(int*) * 8);
    int i;
    int* num;
    for (i = 0; i < 7; ++i)
    {
        num = (int*) malloc(sizeof(int));
        *num = i;
        a[i] = num;
    }
    for (i = 0; i < 7; ++i)
    {
        printf("%d\n", *a[i]);
    }
    return 0;
}

#include<stdio.h>


int CompForInt(void* a, void* b)
{
    if (*(int*) a < *(int*) b)
    {
        return 1;
    }
    return 0;
}


int CompForString(char* a, char* b)
{
    int ind = 0;
    while (a[ind] != '\0' && b[ind] != '\0')
    {
        if (a[ind] < b[ind] || (a[ind] == b[ind] && a[ind + 1] == '\0'))
        {
            return 1;
        }
        if (a[ind] > b[ind] || (a[ind] == b[ind] && b[ind + 1] == '\0'))
        {
            return 0;
        }
        ++ind;
    }
    return 1;
}


int main()
{

    return 0;
}

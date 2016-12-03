#include<stdio.h>

void getBinaryNotationForChar(char* pointer)
{
    int i;
    for (i = 7; i > -1; --i)
    {
        if (*pointer & (1 << i))
        {
            printf("1");
        }
        else
        {
            printf("0");
        }
    }
}

void getBinaryNotation(void* pointer, int num_size)
{
    int i;
    for (i = 0; i < num_size - 1; ++i)
    {
        ++pointer;
    }
    for (i = 0; i < num_size; ++i)
    {
        getBinaryNotationForChar(pointer);
        --pointer;
    }
    printf("\n");
}


int main()
{
    int i = 5;
    printf("binary notation of %d: ", i);
    getBinaryNotation(&i, sizeof(int));

    float f = 1.3;
    printf("binary notation of %f: ", f);
    getBinaryNotation(&f, sizeof(float));

    double d = 0.0001;
    printf("binary notation of %lf: ", d);
    getBinaryNotation(&d, sizeof(double));


    char* s = "hello world";
    printf("binary notation of %s: ", s);
    getBinaryNotation(s, sizeof(s));


    return 0;
}

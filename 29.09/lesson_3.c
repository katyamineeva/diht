#include<stdio.h>

void F_for_char(char* pointer)
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

void F(void* pointer, int num_size)
{
    int i;
    for (i = 0; i < num_size - 1; ++i)
    {
        ++pointer;
    }
    for (i = 0; i < num_size; ++i)
    {
        F_for_char(pointer);
        --pointer;
    }
}

void G_for_char(char* pointer, char* c)
{
    int i;
    *pointer = '\0';
    for (i = 0; i < 8; ++i)
    {
        if (*c == '1')
        {
            *pointer = *pointer + (1 << i);
        }
    }
}

void G(void* pointer, int type_size, int str_size, char* c)
{
    int i;
    int*
    for (i = 0; i < str_size; i + 8)
    {
        G_for_char((char*) pointer, c);
        ++pointer;
        c = c + 8;
    }

}


int main()
{
    float s = 0.5;
    F(&s, sizeof(s));


    return 0;
}

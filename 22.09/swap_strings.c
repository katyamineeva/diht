#define SIZE 1000
#include<stdio.h>

void swap2(char** a, char** b)
{
    char* str3;
    char** c = &str3;
    *c = *a;
    *a = *b;
    *b = *c;
}

void swap(char* a, char* b)
{
    char str3[SIZE];
    char* c = &str3;
    int i;
    for (i = 0; i < SIZE; ++i)
    {
        if (*(a + i) == '\0')
        {
            *(c + i) = *(a + i);
            break;
        }
        *(c + i) = *(a + i);
    }

    for (i = 0; i < SIZE; ++i)
    {
        if (*(b + i) == '\0')
        {
            *(a + i) = *(b + i);
            break;
        }
        *(a + i) = *(b + i);
    }

    for (i = 0; i < SIZE; ++i)
    {
        if (*(c + i) == '\0')
        {
            *(b + i) = *(c + i);
            break;
        }
        *(b + i) = *(c + i);
    }
}

int main()
{
    char str1[SIZE];
    scanf("%s", str1);

    char str2[SIZE];
    scanf("%s", str2);

    swap(str1, str2);
    swap2(&str1, &str2);

    printf("%s\n%s", str1, str2);

    return 0;
}

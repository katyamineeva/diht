#include<stdio.h>
#include<stdlib.h>
#define SIZE 50

int min(int a, int b, int c)
{
    if (a <= b && a <= c)
    {
        return a;
    }
    if (b <= a && b <= c)
    {
        return b;
    }
    return c;
}

int levensteinDistance(char* str1, int strLen1, char* str2, int strLen2)
{
    int i, j;
    int** dp = (int**) malloc((strLen1 + 1) * sizeof(int*));
    for (i = 0; i <= strLen1; ++i)
    {
        dp[i] = (int*) malloc((strLen2 + 1) * sizeof(int));
    }
    dp[0][0] = 0;
    for (j = 1; j <= strLen2; ++j)
    {
        dp[0][j] = dp[0][j - 1] + 1;
    }
    for (i = 1; i <= strLen1; ++i)
    {
        dp[i][0] = dp[i - 1][0] + 1;

        for (j = 1; j <= strLen2; ++j)
        {
            if (str1[i - 1] != str2[j - 1])
            {
                dp[i][j] = min(dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]) + 1;

            }
            else
            {
                dp[i][j] = dp[i - 1][j - 1];
            }
        }
    }
    int levDist = dp[strLen1][strLen2];

    for (i = 0; i <= strLen1; ++i)
    {
        free(dp[i]);
    }
    free(dp);

    return levDist;
}


void readData(char** string1, int* strLen1, char** string2, int* strLen2)
{
    FILE* input = fopen("input.txt", "r");

    int curSize = 0;
    char* str1 = (char*) malloc(SIZE * sizeof(char));
    int maxSize = SIZE;
    char symbol = fgetc(input);

    while (symbol != '\n')
    {
        if (curSize + 1 >= maxSize)
        {
            maxSize = maxSize * 2;
            str1 = (char*) realloc(str1, maxSize * sizeof(char));
        }
        str1[curSize] = symbol;
        symbol = fgetc(input);
        ++curSize;
    }
    str1[curSize] = '\0';
    *strLen1 = curSize;
    *string1 = str1;

    curSize = 0;
    char* str2 = (char*) malloc(SIZE * sizeof(char));
    maxSize = SIZE;
    symbol = fgetc(input);

    while (symbol != '\n')
    {
        if (curSize + 1 >= maxSize)
        {
            maxSize = maxSize * 2;
            str2 = (char*) realloc(str2, maxSize * sizeof(char));
        }
        str2[curSize] = symbol;
        symbol = fgetc(input);
        ++curSize;
    }
    str2[curSize] = '\0';
    *strLen2 = curSize;
    *string2 = str2;

    fclose(input);
}


int main()
{
    int strLen1, strLen2;
    char* str1;
    char* str2;

    readData(&str1, &strLen1, &str2, &strLen2);
    int levDist = levensteinDistance(str1, strLen1, str2, strLen2);
    printf("%d", levDist);

    free(str1);
    free(str2);

    return 0;
}

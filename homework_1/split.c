#include<stdio.h>
#include<stdlib.h>
#define SIZE 50

char* str1;
char* str2;

char** split(int strLen1,
             int strLen2,
             int* ansLen)
{
    int max_x = SIZE;
    int max_y = SIZE;
    char** ans = (char**) malloc(SIZE * sizeof(char*));
    char** tmp1;
    char* tmp2;
    int i, j;
    int flag;
    int x = 0;
    int y = 0;
    for (i = 0; i < SIZE; ++i)
    {
        ans[i] = (char*) malloc(SIZE * sizeof(char));
    }
    i = 0;
    while (i < strLen1)
    {
        flag = 1;
        for (j = 0; j < strLen2; ++j)
        {
            if (i + j >= strLen1 || str1[i + j] != str2[j])
            {
                flag = 0;
                break;
            }
        }
        if (flag)
        {
            i = i + strLen2;
            ans[x][y] = '\0';
            if (y > 0)
            {
                ++x;
            }
            y = 0;
            max_y = SIZE;
        }
        else
        {

            if (x >= max_x)
            {
                tmp1 = (char**) realloc(ans, 2 * max_x * sizeof(char*));
                if (tmp1 != NULL)
                {
                    ans = tmp1;
                }
                else
                {
                    printf("memory error");
                }
                for (j = max_x; j < max_x * 2; ++j)
                {
                    ans[j] = (char*) malloc(SIZE * sizeof(char));
                    if (ans[j] == NULL)
                    {
                        printf("memory error");
                    }
                }
                max_x = max_x * 2;
            }

            ans[x][y] = str1[i];
            ++y;

            if (y >= max_y)
            {
                tmp2 = (char*) realloc(ans[x], 2 * max_y * sizeof(char));
                if (tmp2 != NULL)
                {
                    ans[x] = tmp2;
                }
                max_y = max_y * 2;
            }
            ++i;
        }
    }
    ans[x][y] = '\0';
    if (y == 0)
    {
        *ansLen = x;
    }
    else
    {
        *ansLen = x + 1;
    }

    return ans;
}

void readStrings(int* strLen1, int* strLen2)
{
    FILE* input = fopen("input.txt", "r");

    fscanf(input, "%d", strLen1);
    str1 = (char*) malloc((*strLen1 + 1) * sizeof(char));
    fscanf(input, "%s", str1);

    fscanf(input, "%d", strLen2);
    str2 = (char*) malloc((*strLen2 + 1) * sizeof(char));
    fscanf(input, "%s", str2);

    fclose(input);
}

void writeStrings(char** array, int arrLen)
{
    FILE* output = fopen("output.txt", "w");
    int i, j;
    for (i = 0; i < arrLen; ++i)
    {
        for (j = 0; array[i][j] != '\0'; ++j)
        {
            fprintf(output, "%c", array[i][j]);
        }
        fprintf(output, "\n");
    }
    fclose(output);
}

int main()
{
    int strLen1, strLen2;
    readStrings(&strLen1, &strLen2);
    int ansLen;
    char** ans = split(strLen1, strLen2, &ansLen);
    writeStrings(ans, ansLen);

    int i;
    for (i = 0; i < ansLen; ++i)
    {
        free(ans[i]);
    }
    free(ans);
    free(str1);
    free(str2);
    return 0;
}

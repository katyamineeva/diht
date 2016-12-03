#include<stdio.h>
#include<stdlib.h>
#define SIZE 50


/*
char** readStrings(int* arrLen)
{
    char** a;
    FILE* input = fopen("input.txt", "r");
    if (input == NULL)
    {
        printf("input error");
    }
    else
    {
        fscanf(input, "%d", arrLen);
        a = (char**) malloc(*arrLen * sizeof(char*));
        int i;
        int maxLength;
        char symbol = fgetc(input);
        char* tmp;

        for (i = 0; i < *arrLen; ++i)
        {
            maxLength = SIZE;
            int j;
            a[i] = (char*) malloc(maxLength * sizeof(char));

            for (j = 0; (symbol = getc(input)) != '\n'; ++j)
            {
                if (j >= maxLength - 1)
                {
                    tmp = (char*) realloc(a[i], maxLength * 2 * sizeof(char));
                    if (tmp == NULL)
                    {
                        printf("error");
                        break;
                    }
                    else
                    {
                        a[i] = tmp;
                        maxLength = maxLength * 2;
                    }
                }
                a[i][j] = symbol;
            }
            a[i][j] = '\0';
        }
    }
    fclose(input);
    return a;
}
*/

void split(char* str1, char* str2)
{

}

void readStrings(int* strLen1, int* strLen2, char** str1, char** str2)
{
    FILE* input = fopen("input.txt", "r");

    fscanf(input, "%d", strLen1);
    *str1 = (char*) malloc((*strLen1 + 1) * sizeof(char));
    fscanf(input, "%s", str1);

    fscanf(input, "%d", strLen2);
    *str2 = (char*) malloc((*strLen2 + 1) * sizeof(char));
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
    char** str1 = (char**) malloc(sizeof(char*));
    char** str2 = (char**) malloc(sizeof(char*));

    readStrings(&strLen1, &strLen2, str1, str2);
    split(str1, str2);

    free(str1);
    free(str2);
    return 0;
}

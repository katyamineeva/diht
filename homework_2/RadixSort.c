#include<stdio.h>
#include<stdlib.h>
#define MaxDigit 9

int GetDigit(int a, int i, int* pows)
{
    return (a / pows[i]) % 10;
}

int max(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    return b;
}

void RadixSort(int* a, int NumOfDigits, int* pows, int ArrLen)
{
    int* array[2];
    int cur = 0;
    int other = 1;
    array[cur] = a;
    array[other] = (int*) malloc(ArrLen * sizeof(int));
    int* index = (int*) malloc(MaxDigit * sizeof(int));
    int i, j, digit, tmp, cnt;

    for (i = 0; i < NumOfDigits; ++i)
    {
        int* index = (int*) malloc(sizeof(int) * MaxDigit);
        for(j = 0; j < MaxDigit; ++j)
        {
            index[j] = 0;
        }

        for (j = 0; j < ArrLen; ++j)
        {
            digit = GetDigit(array[cur][j], i, pows);
            ++index[digit];
        }
        cnt = 0;
        for (j = 0; j < MaxDigit; ++j)
        {
            tmp = index[j];
            index[j] = cnt;
            cnt = cnt + tmp;
        }

        other = (cur + 1) % 2;
        for (j = 0; j < ArrLen; ++j)
        {
            digit = GetDigit(array[cur][j], i, pows);
            array[other][index[digit]] = array[cur][j];
            ++index[digit];
        }
        cur = other;
    }
    if (NumOfDigits % 2)
        memcpy(a, array[cur], sizeof(int) * ArrLen);
}


int GetRank(int a)
{
    int rank = 0;
    while (a != 0)
    {
        a = a / 10;
        ++rank;
    }
    return rank;
}

int GetMaxRank(int* arr, int ArrLen)
{
    int MaxRank = GetRank(arr[0]);

    int i;
    for (i = 1; i < ArrLen; ++i)
    {
        MaxRank = max(MaxRank, GetRank(arr[i]));
    }
    return MaxRank;
}

int* GetPows(int n)
{
    int i;
    int* pows = (int*) malloc((n + 1) * sizeof(int));
    pows[0] = 1;
    for (i = 1; i <= n; ++i)
    {
        pows[i] = pows[i - 1] * 10;
    }
    return pows;
}

int* ReadData(int* arrLen)
{
    FILE* input = fopen("input.txt", "r");
    fscanf(input, "%d", arrLen);


    int* array = (int*) malloc(*arrLen * sizeof(int));
    int i;
    for (i = 0; i < *arrLen; ++i)
    {
        fscanf(input, "%d", &array[i]);
    }
    fclose(input);
    return array;
}

void WriteData(int* a, int arrLen)
{
    FILE* output = fopen("output.txt", "w");

    int i;
    for (i = 0; i < arrLen; ++i)
    {
        fprintf(output, "%d ", a[i]);
    }
    fclose(output);
}

void PrintData(int* a, int arrLen)
{
    int i;
    for (i = 0; i < arrLen; ++i)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}


int main()
{
    int arrLen;
    int* arr = ReadData(&arrLen);

    int MaxRank = GetMaxRank(arr, arrLen);
    int* pows = GetPows(MaxRank);
    RadixSort(arr, MaxRank, pows, arrLen);
    PrintData(arr, arrLen);

    free(pows);
    free(arr);

    return 0;
}

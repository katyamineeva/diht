#include<stdio.h>

void Swap(int* x, int* y)
{
    int tmp = *x;
    *x = *y;
    *y = tmp;
}


int Partition(int* a, int left, int right, int pivot)
{
    Swap(&a[right], &a[pivot]);
    int PivotInd = right;
    --right;
    int PivotValue = a[PivotInd];

    while (left < right)
    {

        while (a[left] <= PivotValue && left < right)
        {
            ++left;
        }
        while (a[right] >= PivotValue && left < right)
        {
            --right;
        }
        Swap(&a[left], &a[right]);

        if (left + 1 == right)
        {
            break;
        }
        if (right - left > 1)
        {
            ++left;
            --right;
        }
    }

    if (a[right] >= PivotValue)
    {
        Swap(&a[right], &a[PivotInd]);
        PivotInd = right;
    }
    else
    {
        Swap(&a[right + 1], &a[PivotInd]);
        PivotInd = right + 1;
    }
    return PivotInd;
}

void QuickSort(int* a, int left, int right)
{
    if (right - left > 0)
    {
        int pivot = Partition(a, left, right, right);
        QuickSort(a, left, pivot - 1);
        QuickSort(a, pivot + 1, right);
    }
}


int* ReadData(int* n)
{
    FILE* input = fopen("input.txt", "r");
    fscanf(input, "%d", n);


    int* a = (int*) malloc(*n * sizeof(int));
    int i;
    for (i = 0; i < *n; ++i)
    {
        fscanf(input, "%d", &a[i]);
    }
    fclose(input);
    return a;
}

void WriteData(int* a, int n)
{
    FILE* output = fopen("output.txt", "w");

    int i;
    for (i = 0; i < n; ++i)
    {
        fprintf(output, "%d ", a[i]);
    }
    fclose(output);
}

void PrintData(int* a, int n)
{
    int i;
    for (i = 0; i < n; ++i)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}


int* getRandomArray(int length, int minValue, int maxValue)
{
    int* a = (int*) malloc(length * sizeof(int));
    srand(57);

    int i;
    for (i = 0; i < length; ++i)
    {
        a[i] = minValue + rand() % (maxValue - minValue);
    }
    return a;
}


int main()
{
    int arrLen = 1000000;
    int* a = getRandomArray(arrLen);
    QuickSort(a, 0, arrLen - 1);
    WriteData(a, arrLen);

    free(a);

    return 0;
}

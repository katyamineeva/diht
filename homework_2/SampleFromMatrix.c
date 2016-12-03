#include<stdio.h>
#include<stdlib.h>

int** matrix;
int* vector;

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

int kOrderStatistic(int* a, int left, int right, int k)
{
    if (left == right)
    {
        return a[left];
    }
    else
    {
        int place = Partition(a, left, right, right);
        if (place == k)
        {
            return a[place];
        }
        if (k < place)
        {
            kOrderStatistic(a, left, place - 1, k);
        }
        else
        {
            kOrderStatistic(a, place + 1, right, k);
        }
    }
}

int* GetVector(int n, int m)
{
    int* ans = (int*) malloc(m * sizeof(int));

    int i;
    for (i = 0; i < m; ++i)
    {
        ans[i] = kOrderStatistic(matrix[i], 0, n - 1, vector[i]);
    }
    return ans;
}

void ReadData(int* n, int* m)
{
    FILE* input = fopen("input.txt", "r");
    fscanf(input, "%d %d", n, m);


    matrix = (int**) malloc(*m * sizeof(int*));
    int i, j;
    for (i = 0; i < *m; ++i)
    {
        matrix[i] = malloc(*n * sizeof(int));
    }

    for (i = 0; i < *m; ++i)
    {
        for (j = 0; j < *n; ++j)
        {
            fscanf(input, "%d", &matrix[i][j]);
        }
    }

    vector = malloc(*m * sizeof(int));
    for (i = 0; i < *m; ++i)
    {
        fscanf(input, "%d", &vector[i]);
    }
    fclose(input);
}

void WriteData(int* a, int m)
{
    FILE* output = fopen("output.txt", "w");

    int i;
    for (i = 0; i < m; ++i)
    {
        fprintf(output, "%d ", a[i]);
    }
    fclose(output);
}

void PrintData(int* a, int m)
{
    int i;
    for (i = 0; i < m; ++i)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int main()
{
    int n, m;
    ReadData(&n, &m);
    WriteData(GetVector(n, m), m);

    free(matrix);
    free(vector);
    return 0;
}

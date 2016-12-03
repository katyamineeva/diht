#include<stdio.h>
#include<stdlib.h>

double kahanSum(double* array, int arrLen)
{
    double sum = 0;
    double compensation = 0;
    double tmp;
    int i;

    for (i = 0; i < arrLen; ++i)
    {
        tmp = sum + (array[i] - compensation);
        compensation = tmp - sum - (array[i] - compensation);
        sum = tmp;
    }
    return sum;

}

double* rdeadData(int* n)
{
    FILE* input = fopen("input.txt", "r");
    fscanf(input, "%d", n);


    double* a = (double*) malloc(*n * sizeof(double));
    int i;
    for (i = 0; i < *n; ++i)
    {
        fscanf(input, "%lf", &a[i]);
    }
    fclose(input);
    return a;
}

double usualSum(double* array, int arrLen)
{
    int i;
    double sum = 0;
    for (i = 0; i < arrLen; ++i)
    {
        sum = sum + array[i];
    }
    return sum;
}

int main()
{
    int arrLen;
    // for example array 1000000 0.0000002 0.082 0.00000000001 300000
    double* array = readData(&arrLen);

    printf("difference between usual and kahan summation: %.11lf\n", kahanSum(array, arrLen) - usualSum(array, arrLen));
    return 0;
}

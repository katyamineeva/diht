#include<stdio.h>
#include<stdlib.h>

void merge(int* array, int* buffer, int left, int middle, int right)
{
    int i = 0;
    int j = 0;
    while (left + i < middle && middle + j < right)
    {
        if (array[left + i] < array[middle + j])
        {
            buffer[left + i + j] = array[left + i];
            ++i;
        }
        else
        {
            buffer[left + i + j] = array[middle + j];
            ++j;
        }
    }
    while (left + i < middle)
    {
        buffer[left + i + j] = array[left + i];
        ++i;
    }
    while (middle + j < right)
    {
        buffer[left + i + j] = array[middle + j];
        ++j;
    }
    int ind;
    for (ind = 0; ind < (right - left); ++ind)
    {
        array[left + ind] = buffer[left + ind];
    }
}



void mergeSort(int** array, int left, int right)
{
    if (right - left > 1)
    {
        int middle = (left + right) / 2;
        mergeSort(array, left, middle);
        mergeSort(array, middle, right);

        merge(array[0], array[1], left, middle, right);
    }
}


int* readData(int* arrLen)
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

void writeData(int* array, int arrLen)
{
    FILE* output = fopen("output.txt", "w");

    int i;
    for (i = 0; i < arrLen; ++i)
    {
        fprintf(output, "%d ", array[i]);
    }
    fclose(output);
}

void printData(int* array, int arrLen)
{
    int i;
    for (i = 0; i < arrLen; ++i)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}



void swap(void* x, void* y, size_t size)
{
    char* x1 = (char*) x;
    char* y1 = (char*) y;
    int i;
    char tmp;
    for (i = 0; i < size; ++i)
    {
        tmp = *(x1 + i);
        *(x1 + i) = *(y1 + i);
        *(y1 + i) = tmp;
    }
    x = (void*) x1;
    y = (void*) y1;
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
    int arrLen;
    int** array = (int**) malloc(2 * sizeof(int*));
    array[0] = readData(&arrLen);
    array[1] = (int*) malloc(arrLen * sizeof(int));

    mergeSort(array, 0, arrLen);
    printData(array[0], arrLen);

    free(array[0]);
    free(array[1]);
    free(array);

    return 0;
}

#include<stdio.h>
#include<stdlib.h>
#define SIZE 50

int arrLen;
int indOfStart;

int* getSequence()
{
    int* seq = (int*) malloc(SIZE * sizeof(int));
    int* tmp;
    int maxLength = SIZE;
    seq[0] = 1;
    int i = 1;
    while (seq[i - 1] < arrLen)
    {
        if (i >= maxLength)
        {

            tmp = (int*) realloc(seq, maxLength * 2 * sizeof(int));
            if (tmp == NULL)
            {
                return NULL;
            }
            else
            {
                seq = tmp;
                maxLength = maxLength * 2;
            }
        }
        seq[i] = seq[i - 1] * 2 + 1;
        ++i;
    }
    indOfStart = i - 2;
    return seq;
}

void hSort(int* array, int h)
{
    int i, ind;
    for (i = 1; i < arrLen; i = i + h)
    {
        ind = i;

        while (ind >= h && array[ind] < array[ind - h])
        {
            swap(&array[ind], &array[ind - h], sizeof(array[ind]));
            ind = ind - h;
        }
    }
}

void shellSort(int* array)
{
    int* seq = getSequence();
    int i;
    for (i = indOfStart; i >= 0; --i)
    {
        hSort(array, seq[i]);
    }
    free(seq);
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


int* readData()
{
    FILE* input = fopen("input.txt", "r");
    fscanf(input, "%d", &arrLen);


    int* array = (int*) malloc(arrLen * sizeof(int));
    int i;
    for (i = 0; i < arrLen; ++i)
    {
        fscanf(input, "%d", &array[i]);
    }
    fclose(input);
    return array;
}

void writeData(int* array)
{
    FILE* output = fopen("output.txt", "w");

    int i;
    for (i = 0; i < arrLen; ++i)
    {
        fprintf(output, "%d ", array[i]);
    }
    fclose(output);
}

void printData(int* array)
{
    int i;
    for (i = 0; i < arrLen; ++i)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main()
{
    int* a = readData();
    shellSort(a);
    printData(a);
    free(a);
    return 0;
}

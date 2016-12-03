#include<stdio.h>
#include<stdlib.h>
#define EPS 0.000000001
#define SIZE 50

typedef struct Node Node;
typedef struct Heap Heap;

struct Heap
{
    int size;
    int maxSize;
    size_t elemSize;
    int (*cmp)(void* , void* );
    void* elements;
};



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



void assignmentForChar(char* x, char* y)
{
    *x = *y;
}

void assignment(void* x, void* y, size_t size)
{
    char* x1 = (char*) x;
    char* y1 = (char*) y;
    int i;
    for (i = 0; i < size; ++i)
    {
        assignmentForChar(x1 + i, y1 + i);
    }
    x = (void*) x1;
    y = (void*) y1;
}


void* max(void* a, void* b, int (*cmp)(void *, void *))
{
    if (cmp(a, b))
    {
        return b;
    }
    return a;
}

int compForString(void* x, void* y)
{
    char *a = *(char**) x;
    char *b = *(char**) y;
    int ind = 0;
    while (a[ind] != '\0' && b[ind] != '\0')
    {
        if (a[ind] < b[ind])
        {
            return 1;
        }
        if (a[ind] > b[ind])
        {
            return 0;
        }
        ++ind;
    }
    return 1;
}


int compForInt(void* a, void* b)
{
    int* x = (int*) a;
    int* y = (int*) b;
    if (*x <= *y)
    {
        return 1;
    }
    return 0;
}

int compForDouble(void* a, void* b)
{
    double* x = (double*) a;
    double* y = (double*) b;
    if (EPS <= *y - *x)
    {
        return 1;
    }
    return 0;
}


void* getLeftChild(Heap* myheap, int ind, size_t size)
{
    if (ind * 2 + 1 < myheap->size)
    {
        return (void*)(myheap->elements + (ind * 2 + 1) * size);
    }
    return NULL;
}


void* getRightChild(Heap* myheap, int ind, size_t size)
{
    if (ind * 2 + 2 < myheap->size)
    {
        return (void*)(myheap->elements + (ind * 2 + 2) * size);
    }
    return NULL;
}


int* getParent(Heap* myheap, int ind, size_t size)
{
    if (ind != 0)
    {
        return (void*)(myheap->elements + ((ind - 1) / 2) * size);
    }
    return NULL;
}

void siftDown(Heap* myheap, int ind, size_t size, int (*cmp)(void *, void *))
{
    void* leftChild = getLeftChild(myheap, ind, size);
    void* rightChild = getRightChild(myheap, ind, size);

    if (leftChild != NULL && rightChild == NULL)
    {
        if (cmp(myheap->elements + ind * size, leftChild))
        {
            swap(leftChild, myheap->elements + ind * size, size);
        }
    }
    if (rightChild != NULL)
    {
        if (cmp(max(myheap->elements + ind * size, rightChild, cmp), leftChild))
        {
            swap(myheap->elements + ind * size, leftChild, size);
            siftDown(myheap, ind * 2 + 1, size, cmp);
        }
        if (!cmp(rightChild, max(myheap->elements + ind * size, leftChild, cmp)))
        {
            swap(myheap->elements + ind * size, rightChild, size);
            siftDown(myheap, ind * 2 + 2, size, cmp);
        }
    }
}

void extractMax(Heap* myheap, size_t size, int (*cmp)(void *, void *))
{
    if (myheap->size == 0)
    {
        printf("error");
    }
    else
    {
        swap(myheap->elements, myheap->elements + (myheap->size - 1) * size, size);
        --myheap->size;
        siftDown(myheap, 0, size, cmp);
    }
}

Heap* buildHeap(void* array, int arrLen, size_t size, int (*cmp)(void *, void *))
{
    Heap* myheap = (Heap*) malloc(sizeof(Heap));
    myheap->size = arrLen;
    myheap->maxSize = arrLen;
    myheap->elements = array;
    myheap->cmp = cmp;

    int i;
    for (i = arrLen / 2; i >= 0; --i)
    {
        siftDown(myheap, i, size, cmp);
    }
    return myheap;
}

void heapSort(void* array, int arrLen, size_t size, int (*cmp)(void *, void *))
{
    Heap* myheap = buildHeap(array, arrLen,  size, cmp);
    int i;
    for (i = arrLen - 1; i >= 0; --i)
    {
        extractMax(myheap, size, cmp);
    }
}


int* readInts()
{
    FILE* input = fopen("input.txt", "r");
    fscanf(input, "%d", &arrLen);


    int* a = (int*) malloc(arrLen * sizeof(int));
    int i;
    for (i = 0; i < arrLen; ++i)
    {
        fscanf(input, "%d", &a[i]);
    }
    fclose(input);
    return a;
}

void writeInts(int* a)
{
    FILE* output = fopen("output.txt", "w");

    int i;
    for (i = 0; i < arrLen; ++i)
    {
        fprintf(output, "%d ", a[i]);
    }
    fclose(output);
}


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
        a = (char**) malloc(arrLen * sizeof(char*));
        int i;
        int maxLength;
        char symbol = fgetc(input);
        char* tmp;

        for (i = 0; i < arrLen; ++i)
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

void writeStrings(char** array)
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

double* readDoubles()
{
    FILE* input = fopen("input.txt", "r");
    fscanf(input, "%d", &arrLen);


    double* a = (double*) malloc(arrLen * sizeof(double));
    int i;
    for (i = 0; i < arrLen; ++i)
    {
        fscanf(input, "%lf", &a[i]);
    }
    fclose(input);
    return a;
}

void writeDoubles(double* a)
{
    FILE* output = fopen("output.txt", "w");

    int i;
    for (i = 0; i < arrLen; ++i)
    {
        fprintf(output, "%lf ", a[i]);
    }
    fclose(output);
}

int main()
{
    int arrLen;
    int* array = readInts(&arrLen);
    heapSort(array, arrLen, sizeof(int), compForInt);
    writeInts(array);

    free(array);
    return 0;
}

#include<stdio.h>
#include<stdlib.h>
#define rightBorder 100000

typedef struct Node Node;
typedef struct Heap Heap;
typedef struct Segment Segment;

struct Segment
{
    int start;
    int end;
};

struct Heap
{
    int size;
    int maxSize;
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


void* max(void* a, void* b, int (*cmp)(void *, void *))
{
    if (cmp(a, b))
    {
        return b;
    }
    return a;
}

int compForSegments(Segment* a, Segment* b)
{
    if (a->start < b->start || (a->start == b->start && a->end <= b->end))
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

    int i;
    for (i = arrLen / 2; i >= 0; --i)
    {
        siftDown(myheap, i, size, cmp);
    }
    return myheap;
}

void heapSort(void* array, int arrLen, size_t size, int (*cmp)(void *, void *))
{
    Heap* myheap = buildHeap(array, arrLen, size, cmp);
    int i;
    for (i = arrLen - 1; i >= 0; --i)
    {
        extractMax(myheap, size, cmp);
    }
}


Segment* getCovering(Segment* array, int arrLen, int* cntSegments)
{
    heapSort(array, arrLen, sizeof(Segment), compForSegments);

    Segment* covering = (Segment*) malloc(sizeof(Segment) * arrLen);
    int ind = 0;
    int leftBorder = 0;
    *cntSegments = 0;
    while (ind < arrLen && (*cntSegments == 0 || covering[*cntSegments - 1].end < rightBorder))
    {
        if (array[ind].start > leftBorder)
        {
            printf("error");
            return NULL;
        }
        while (array[ind].start <= leftBorder)
        {
            ++ind;
        }
        covering[*cntSegments] = array[ind - 1];
        leftBorder = array[ind - 1].end;
        ++ *cntSegments;
    }
    return covering;
}

Segment* readData(int* arrLen)
{
    FILE* input = fopen("input.txt", "r");
    fscanf(input, "%d", arrLen);

    Segment* array = (Segment*) malloc(*arrLen * sizeof(Segment));

    int i;
    for (i = 0; i < *arrLen; ++i)
    {
        fscanf(input, "%d %d", &array[i].start, &array[i].end);
    }
    fclose(input);
    return array;
}

void printData(Segment* array, int arrLen)
{
    int i;
    for (i = 0; i < arrLen; ++i)
    {
        printf("%d %d\n", array[i].start, array[i].end);
    }
}

int main()
{
    int arrLen;
    Segment* array = readData(&arrLen);
    int cntSegments;
    Segment* res = getCovering(array, arrLen, &cntSegments);
    printData(res, cntSegments);

    free(array);
    free(res);
    return 0;
}

#include<stdio.h>
#include<stdlib.h>

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
    if (a->end < b->end || (a->end == b->end && a->start <= b->start))
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


Segment* getApplications(Segment* array, int arrLen, int* cntSegments)
{
    heapSort(array, arrLen, sizeof(Segment), compForSegments);
    Segment* applications = (Segment*) malloc(sizeof(Segment) * arrLen);
    applications[0] = array[0];
    int i;
    int ind = 1;
    int border = array[0].end;
    for (i = 1; i < arrLen; ++i)
    {
        if (array[i].start >= border)
        {
            applications[ind] = array[i];
            ++ind;
            border = array[i].end;
        }
    }
    *cntSegments = ind;
    return applications;
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
    Segment* res = getApplications(array, arrLen, &cntSegments);
    printData(res, cntSegments);

    free(array);
    return 0;
}

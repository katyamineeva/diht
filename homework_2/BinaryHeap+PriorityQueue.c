#include<stdio.h>
#include<stdlib.h>
typedef struct Node Node;
typedef struct Heap Heap;

struct Heap
{
    int size;
    int maxSize;
    int* elements;
};

int max(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    return b;
}


void swap(int* x, int* y)
{
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

int getSize(Heap* myheap)
{
    return myheap->size;
}

int* getLeftChild(Heap* myheap, int ind)
{
    if (ind * 2 + 1 < myheap->size)
    {
        return &myheap->elements[ind * 2 + 1];
    }
    return NULL;
}


int* getRightChild(Heap* myheap, int ind)
{
    if (ind * 2 + 2 < myheap->size)
    {
        return &myheap->elements[ind * 2 + 2];
    }
    return NULL;
}


int* getParent(Heap* myheap, int ind)
{
    if (ind != 0)
    {
        return &myheap->elements[(ind - 1) / 2];
    }
    return NULL;
}

int getMaximum(Heap* myheap)
{
    return myheap->elements[0];
}

void siftDown(Heap* myheap, int ind)
{
    int* leftChild = getLeftChild(myheap, ind);
    int* rightChild = getRightChild(myheap, ind);

    if (leftChild != NULL && rightChild == NULL)
    {
        if (*leftChild > myheap->elements[ind])
        {
            swap(leftChild, &myheap->elements[ind]);
        }
    }
    if (rightChild != NULL)
    {
        if (max(myheap->elements[ind], *rightChild) < *leftChild)
        {
            swap(&myheap->elements[ind], leftChild);
            siftDown(myheap, ind * 2 + 1);
        }
        if (max(myheap->elements[ind], *leftChild) < *rightChild)
        {
            swap(&myheap->elements[ind], rightChild);
            siftDown(myheap, ind * 2 + 2);
        }
    }
}


void siftUp(Heap* myheap, int ind)
{
    int* parent = getParent(myheap, ind);
    if (parent != NULL && *parent < myheap->elements[ind])
    {
        swap(parent, &myheap->elements[ind]);
        siftUp(myheap, (ind - 1) / 2);
    }
}

void addElement(Heap* myheap, int value)
{
    if (myheap->size < myheap->maxSize)
    {
        myheap->elements[myheap->size] = value;
        siftUp(myheap, myheap->size);
        ++myheap->size;
    }
    else
    {
        int* tmp = (int*) realloc(myheap->elements, myheap->maxSize * 2 * sizeof(int));
        if (tmp != NULL)
        {
            myheap->elements = tmp;
            myheap->elements[myheap->size] = value;
            ++myheap->size;
            myheap->maxSize = myheap->maxSize *  2;
            siftUp(myheap, myheap->size - 1);
        }
        else
        {
            printf("error");
        }
    }
}

void extractMax(Heap* myheap)
{
    if (myheap->size == 0)
    {
        printf("error");
    }
    else
    {
        swap(&myheap->elements[0], &myheap->elements[myheap->size - 1]);
        --myheap->size;
        siftDown(myheap, 0);
    }

}

Heap* buildHeap(int* array, int arrLen)
{
    Heap* myheap = (Heap*) malloc(sizeof(Heap));
    myheap->size = arrLen;
    myheap->maxSize = arrLen;
    myheap->elements = array;

    int i;
    for (i = arrLen / 2; i >= 0; --i)
    {
        siftDown(myheap, i);
    }
    return myheap;
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

void printHeap(Heap* myheap, int arrLen)
{
    FILE* output = fopen("output.txt", "w");

    int i;
    for (i = 0; i < myheap->size; ++i)
    {
        fprintf(output, "%d ", myheap->elements[i]);
    }
    fclose(output);

}

int main()
{
    int arrLen;
    int maximum;
    int* array = readData(&arrLen);
    Heap* myheap = buildHeap(array, arrLen);
    maximum = getMaximum(myheap);
    printf("%d\n", maximum);
    addElement(myheap, 88);
    maximum = getMaximum(myheap);
    printf("%d", maximum);
    printHeap(myheap, arrLen);
    free(array);
    return 0;
}

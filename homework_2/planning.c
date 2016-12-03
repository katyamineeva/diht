#include<stdio.h>
#include<stdlib.h>
#define EPS 0.0000000001
#define SIZE_OF_COMMAND 8
#define SIZE_OF_GUID 3

typedef struct Node Node;
typedef struct Heap Heap;

typedef struct
{
    double priority;
    char* guid;
} Problem;

struct Heap
{
    int size;
    int maxSize;
    Problem* elements;
};

double min(double a, double b)
{
    if ((b - a) > EPS)
    {
        return a;
    }
    return b;
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


int getSize(Heap* myheap)
{
    return myheap->size;
}

Problem* getLeftChild(Heap* myheap, int ind)
{
    if (ind * 2 + 1 < myheap->size)
    {
        return &myheap->elements[ind * 2 + 1];
    }
    return NULL;
}


Problem* getRightChild(Heap* myheap, int ind)
{
    if (ind * 2 + 2 < myheap->size)
    {
        return &myheap->elements[ind * 2 + 2];
    }
    return NULL;
}


Problem* getParent(Heap* myheap, int ind)
{
    if (ind != 0)
    {
        return &myheap->elements[(ind - 1) / 2];
    }
    return NULL;
}

Problem getMinimum(Heap* myheap)
{
    return myheap->elements[0];
}

void siftDown(Heap* myheap, int ind)
{
    Problem* leftChild = getLeftChild(myheap, ind);
    Problem* rightChild = getRightChild(myheap, ind);

    if (leftChild != NULL && rightChild == NULL)
    {
        if (EPS < myheap->elements[ind].priority - leftChild->priority)
        {
            swap(leftChild, &myheap->elements[ind], sizeof(Problem));
        }
    }
    if (rightChild != NULL)
    {
        if (min(myheap->elements[ind].priority, rightChild->priority) - leftChild->priority > EPS)
        {
            swap(&myheap->elements[ind], leftChild, sizeof(Problem));
            siftDown(myheap, ind * 2 + 1);
        }
        if (min(myheap->elements[ind].priority, leftChild->priority) - rightChild->priority > EPS)
        {
            swap(&myheap->elements[ind], rightChild, sizeof(Problem));
            siftDown(myheap, ind * 2 + 2);
        }
    }
}


void siftUp(Heap* myheap, int ind)
{
    Problem* parent = getParent(myheap, ind);
    if (parent != NULL && (parent->priority - myheap->elements[ind].priority) > EPS)
    {
        swap(parent, &myheap->elements[ind], sizeof(Problem));
        siftUp(myheap, (ind - 1) / 2);
    }
}

void addElement(Heap* myheap, double pr, char* g)
{
    Problem* ptr;
    if (myheap->size >= myheap->maxSize)
    {
        ptr = (Problem*) realloc(myheap->elements, myheap->maxSize * 2 * sizeof(Problem));
        if (ptr == NULL)
        {
            printf("error");
        }
        else
        {
            myheap->elements = ptr;
            myheap->maxSize = myheap->maxSize * 2;
        }
    }
    Problem tmp;
    tmp.priority = pr;
    tmp.guid = (char*) malloc(SIZE_OF_GUID * sizeof(char));
    int i;
    for (i = 0; i < SIZE_OF_GUID; ++i)
    {
        tmp.guid[i] = g[i];
    }
    myheap->elements[myheap->size] = tmp;
    ++myheap->size;
    siftUp(myheap, myheap->size - 1);
}


void extractMin(Heap* myheap)
{
    if (myheap->size == 0)
    {
        printf("error");
    }
    else
    {
        swap(&myheap->elements[0], &myheap->elements[myheap->size - 1], sizeof(Problem));
        --myheap->size;
        siftDown(myheap, 0);
    }

}

Heap* buildHeap(Problem* array, int arrLen)
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


void deleteHeap(Heap* myheap, int arrLen)
{
    int i;
    for (i = 0; i < arrLen; ++i)
    {
        free(myheap->elements[i].guid);
    }
    free(myheap->elements);
    free(myheap);
}

Problem* readData(int* arrLen)
{
    FILE* input = fopen("input.txt", "r");
    fscanf(input, "%d", arrLen);

    Problem* array = (Problem*) malloc(*arrLen * sizeof(Problem));
    int i;
    for (i = 0; i < *arrLen; ++i)
    {
        array[i].guid = (char*) malloc(SIZE_OF_GUID * sizeof(char));
        fscanf(input, "%lf %s", &array[i].priority, array[i].guid);
    }
    fclose(input);
    return array;
}


void someTests()
{
    int arrLen;
    Problem* array = readData(&arrLen);
    Heap* myheap = buildHeap(array, arrLen);

    FILE* input = fopen("commands.txt", "r");

    double pr;
    char* command = (char*) malloc(SIZE_OF_COMMAND * sizeof(char));
    char* name = (char*) malloc(SIZE_OF_GUID * sizeof(char));

    fscanf(input, "%s", command);
    while (command[0] != 'F')
    {
        if (command[0] == 'A')
        {
            fscanf(input, "%lf %s", &pr, name);
            addElement(myheap, pr, name);
            printf("%lf\n", getMinimum(myheap).priority);
        }
        if (command[0] == 'P')
        {
            printf("%s\n", getMinimum(myheap).guid);
            extractMin(myheap);
        }
        fscanf(input, "%s", command);

    }

    fclose(input);

    deleteHeap(myheap, arrLen);
    free(array);
    free(command);
    free(name);
}

int main()
{
    someTests();
    return 0;
}

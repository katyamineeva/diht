#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define SIZE 50

#define SIZE1 1000
#define SIZE2 10000
#define SIZE3 1000000


int arrLen;
int indOfStart;

typedef struct Node Node;
typedef struct Heap Heap;


struct Heap
{
    int size;
    int maxSize;
    int* elements;
};


void swapForChar(char* x, char* y)
{
    char tmp = *x;
    *x = *y;
    *y = tmp;
}

void swap(void* x, void* y, size_t size)
{
    char* x1 = (char*) x;
    char* y1 = (char*) y;
    int i;
    for (i = 0; i < size; ++i)
    {
        swapForChar(x1 + i, y1 + i);
    }
    x = (void*) x1;
    y = (void*) y1;
}

int max(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    return b;
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

void siftDown(Heap* myheap, int ind)
{
    int* leftChild = getLeftChild(myheap, ind);
    int* rightChild = getRightChild(myheap, ind);

    if (leftChild != NULL && rightChild == NULL)
    {
        if (*leftChild > myheap->elements[ind])
        {
            swap(leftChild, &myheap->elements[ind], sizeof(leftChild));
        }
    }
    if (rightChild != NULL)
    {
        if (max(myheap->elements[ind], *rightChild) < *leftChild)
        {
            swap(&myheap->elements[ind], leftChild, sizeof(leftChild));
            siftDown(myheap, ind * 2 + 1);
        }
        if (max(myheap->elements[ind], *leftChild) < *rightChild)
        {
            swap(&myheap->elements[ind], rightChild, sizeof(rightChild));
            siftDown(myheap, ind * 2 + 2);
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
        swap(&myheap->elements[0], &myheap->elements[myheap->size - 1], sizeof(int*));
        --myheap->size;
        siftDown(myheap, 0);
    }

}

int getMaximum(Heap* myheap)
{
    return myheap->elements[0];
}


Heap* buildHeap(int* array)
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

void heapSort(int* array)
{
    Heap* myheap = buildHeap(array);
    int* res = (int*) malloc(arrLen * sizeof(int));
    int i;
    for (i = arrLen - 1; i >= 0; --i)
    {
        res[i] = getMaximum(myheap);
        extractMax(myheap);
    }
}


int partition(int* a, int left, int right, int pivot)
{
    swap(&a[right], &a[pivot], sizeof(int));
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
        swap(&a[left], &a[right], sizeof(int));

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
        swap(&a[right], &a[PivotInd], sizeof(int));
        PivotInd = right;
    }
    else
    {
        swap(&a[right + 1], &a[PivotInd], sizeof(int));
        PivotInd = right + 1;
    }
    return PivotInd;
}

void quickSort(int* a, int left, int right)
{
    if (right - left > 0)
    {
        int pivot = partition(a, left, right, right);
        quickSort(a, left, pivot - 1);
        quickSort(a, pivot + 1, right);
    }
}



void merge(int** array, int left, int middle, int right)
{
    int i = 0;
    int j = 0;

    while (left + i < middle && middle + j < right)
    {
        if (array[0][left + i] < array[0][middle + j])
        {
            array[1][i + j] = array[0][left + i];
            ++i;
        }
        else
        {
            array[1][i + j] = array[0][middle + j];
            ++j;
        }
    }
    while (left + i < middle)
    {
        array[1][i + j] = array[0][left + i];
        ++i;
    }
    while (middle + j < right)
    {
        array[1][i + j] = array[0][middle + j];
        ++j;
    }
    int ind;
    for (ind = 0; ind < (right - left); ++ind)
    {
        array[0][left + ind] = array[1][ind];
    }
}



void mergeSort(int** array, int left, int right)
{
    if (right - left > 1)
    {
        int middle = (left + right) / 2;
        mergeSort(array, left, middle);
        mergeSort(array, middle, right);

        merge(array, left, middle, right);
    }
}



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


void bubble(int* a)
{
    int i, j;
    for (i = 0; i < arrLen; ++i)
    {
        for (j = 0; j < (arrLen - i - 1); ++j)
        {
            if (a[j] > a[j + 1])
            {
                swap(&a[j], &a[j + 1], sizeof(a[j]));
            }
        }
    }

}


int* getSortedArray(int length)
{
    int* a = (int*) malloc(length * sizeof(int));
    int i;
    for (i = 0; i < length; ++i)
    {
        a[i] = i;
    }
    return a;
}


int* getReversedArray(int length)
{
    int* a = (int*) malloc(length * sizeof(int));
    int i;
    for (i = 0; i < length; ++i)
    {
        a[i] = length - i;
    }
    return a;
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


int* getCopy(int* a)
{
    int* b = (int*) malloc(arrLen * sizeof(int));
    int i;
    for (i = 0; i < arrLen; ++i)
    {
        b[i] = a[i];
    }
    return b;
}

void getTime(int* a)
{
    clock_t start, end;
    int* copyOfArray;

    printf("heapSort  ");
    copyOfArray = getCopy(a);
    start = clock();
    heapSort(copyOfArray);
    end = clock();
    printf("%lf\n", (double) (end - start) / (double) CLOCKS_PER_SEC);
    free(copyOfArray);

    printf("bubbleSort  ");
    copyOfArray = getCopy(a);
    start = clock();
    bubble(copyOfArray);
    end = clock();
    printf("%.11lf\n", (double) (end - start) / (double) CLOCKS_PER_SEC);
    free(copyOfArray);

    printf("quickSort  ");
    copyOfArray = getCopy(a);
    start = clock();
    quickSort(copyOfArray, 0, arrLen - 1);
    end = clock();
    printf("%.11lf\n", (double) (end - start) / (double) CLOCKS_PER_SEC);
    free(copyOfArray);


    printf("shellSort  ");
    copyOfArray = getCopy(a);
    start = clock();
    shellSort(copyOfArray);
    end = clock();
    printf("%.11lf\n", (double) (end - start) / (double) CLOCKS_PER_SEC);
    free(copyOfArray);

    printf("mergeSort  ");
    int** arr = (int**) malloc(2 * sizeof(int*));
    arr[0] = getCopy(a);
    arr[1] = (int*) malloc(arrLen * sizeof(int));

    start = clock();
    mergeSort(arr, 0, arrLen);
    end = clock();
    printf("%.11lf\n", (double) (end - start) / (double) CLOCKS_PER_SEC);
    free(arr[0]);
    free(arr[1]);
    free(arr);

}

void someTests(int length)
{
    int *a;
    printf("\n sorted array \n");
    a = getSortedArray(length);
    getTime(a);
    free(a);

    printf("\n reversed array \n");
    a = getReversedArray(length);
    getTime(a);
    free(a);

    printf("\n random array \n");
    a = getRandomArray(length, -length, length);
    getTime(a);
    free(a);

    printf("\n array with often repeated elements\n");
    a = getRandomArray(length, -100, 100);
    getTime(a);
    free(a);

}

int main()
{
    printf("\nsize of array: %d\n", SIZE1);
    arrLen = SIZE1;
    someTests(SIZE1);

    printf("\nsize of array: %d\n", SIZE2);
    arrLen = SIZE2;
    someTests(SIZE2);

    printf("\nsize of array: %d\n", SIZE3);
    arrLen = SIZE3;
    someTests(SIZE3);

    return 0;
}

#include<stdio.h>
#include<stdlib.h>
#define EPS 0.00000001
#define SIZE 50

int arrLen;
int indOfStart;



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

void hSort(void* array, int h, size_t size, int (*cmp)(void *, void *))
{
    int i, ind;
    for (i = 1; i < arrLen; i = i + h)
    {
        ind = i;

        while (ind >= h && cmp((void*)(array + ind * size), (void*)(array + ind * size - h * size)))
        {
            swap((array + ind * size), (array + ind * size - h * size), size);
            ind = ind - h;
        }
    }
}

void shellSort(void* array, size_t size, int (*cmp)(void *, void *))
{
    int* seq = getSequence();
    int i;
    for (i = indOfStart; i >= 0; --i)
    {
        hSort(array, seq[i], size, cmp);
    }
    free(seq);
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


char** readStrings()
{
    char** a;
    FILE* input = fopen("input.txt", "r");
    if (input == NULL)
    {
        printf("input error");
    }
    else
    {
        fscanf(input, "%d", &arrLen);
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
    char** a = readStrings();
    shellSort(a, sizeof(char*), compForString);
    writeStrings(a);
    free(a);
    return 0;
}

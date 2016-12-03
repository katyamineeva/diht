#include<stdio.h>

int n;
char** a;
char s[];


void SwapForChar(char* x, char* y)
{
    char tmp = *x;
    *x = *y;
    *y = tmp;
}

void Swap(void* x, void* y, size_t size)
{
    char* x1 = (char*) x;
    char* y1 = (char*) y;
    char temp;
    int i;
    for (i = 0; i < size; ++i)
    {
        SwapForChar(x1 + i, y1 + i);
    }
    x = (void*) x1;
    y = (void*) y1;
}

int CompForString(char* a, char* b)
{
    int ind = 0;
    while (a[ind] != '\0' && b[ind] != '\0')
    {
        if (a[ind] < b[ind] || (a[ind] == b[ind] && a[ind + 1] == '\0'))
        {
            return 1;
        }
        if (a[ind] > b[ind] || (a[ind] == b[ind] && b[ind + 1] == '\0'))
        {
            return 0;
        }
        ++ind;
    }
    return 1;
}

void ReadData()
{
    FILE* input = fopen("input.txt", "r");
    if (input == NULL)
    {
        printf("input error");
    }
    else
    {
        fscanf(input, "%d", &n);
        a = (char**) malloc(n * sizeof(char*));
        int i;
        for (i = 0; i < n; ++i)
        {
            fscanf(input, "%s", s);

            int length;
            for (length = 0; s[length] != '\0'; ++length);

            a[i] = (char*) malloc((length + 1) * sizeof(char));

            int j;
            for (j = 0; j <= length; ++j)
            {
                a[i][j] = s[j];
            }
        }
    }
    fclose(input);
}

void WriteData()
{
    FILE* output = fopen("output.txt", "w");
    int i, j;
    for (i = 0; i < n; ++i)
    {
        j = 0;
        while (a[i][j] != '\0')
        {
            fprintf(output, "%c", a[i][j]);
            ++j;
        }
        fprintf(output, "%c", '\n');
    }
    fclose(output);
}

void InsertionSort(int* cmp (char*, char*))
{
    int i, ind;
    for (i = 1; i < n; ++i)
    {
        ind = i;
        while (ind > 0 && cmp(a[ind], a[ind - 1]))
        {
            Swap(a[ind], a[ind - 1], sizeof(a[ind]));
            --ind;
        }
    }
}


int main()
{
    ReadData();
    InsertionSort(CompForString);
    WriteData();
    return 0;
}

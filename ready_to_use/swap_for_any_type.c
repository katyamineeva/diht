#include<stdio.h>

int a[3] = {1, 2, 3};

void swap_for_char(char* x, char* y)
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
        swap_for_char(x1 + i, y1 + i);
    }
    x = (void*) x1;
    y = (void*) y1;
}

int main()
{
    printf("%d %d", a[0], a[1]);
    swap(&a[0], &a[1], sizeof(a[0]));
    printf("%d %d", a[0], a[1]);

    return 0;
}

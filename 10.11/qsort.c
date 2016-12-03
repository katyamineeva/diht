#define SIZE 10000
#define eps  5.7e-18
#include<stdio.h>
#include<stdlib.h>


int a[SIZE];
int n;


void swap(void* x, void* y)
{
    write_data_in_stream();
    int tmp = *(int*) x;
    *(int*)x = *(int*)y;
    *(int*)y = tmp;
    write_data_in_stream();
    int nn;
    scanf("%d", &nn);
}


int comp(void* a, void* b)
{
    int a1 = *(int*) a;
    int b1 = *(int*) b;
    if ((b1 - a1) > eps)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int get_value(void* a)
{
    return *(int*) a;
}


void read_data_from_stream()
{
    scanf("%d", &n);

    int i;
    for (i = 0; i < n; ++i)
    {
        scanf("%d", &a[i]);
    }
}

void write_data_in_stream()
{
    int i;
    for (i = 0; i < n; ++i)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void* partition(void* left, void* right)
{
    void* pivot = right;
    --right;
    while (left < right)
    {
        while (get_value(left) < get_value(pivot) && left <= right)
        {
            ++left;
        }
        while (get_value(right) > get_value(pivot) && left <= right)
        {
            --right;
        }

        if (left < right)
        {
            swap(left, right);
            ++left;
            --right;
        }
    }
    if (get_value(right) >= get_value(pivot))
    {
        printf("first ");
        swap(pivot, right);
        return right;
    }
    else
    {
        printf("second ");
        swap(pivot, right + 1);
        return right + 1;

    }

}

void quicksort(void* left, void* right)
{
    if (right - left > 1)
    {
        void* m = partition(left, right);
        quicksort(left, m - 1);

        quicksort(m, right);
    }
}

int main()
{
    read_data_from_stream();
    quicksort(&a[0], &a[n - 1]);
    write_data_in_stream();


    return 0;
}

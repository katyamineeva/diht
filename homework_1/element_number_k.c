#include<stdio.h>
#define SIZE 100000

int a[SIZE];
int n;

void swap(int x, int y)
{
    int tmp = a[x];
    a[x] = a[y];
    a[y] = tmp;
}


int partition(int left, int right, int pivot)
{
    swap(right, pivot);
    int pivot_ind = right;
    --right;
    int pivot_value = a[pivot_ind];

    while (left < right)
    {

        while (a[left] <= pivot_value && left < right)
        {
            ++left;
        }
        while (a[right] >= pivot_value && left < right)
        {
            --right;
        }
        swap(left, right);

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

    if (a[right] >= pivot_value)
    {
        swap(right, pivot_ind);
        pivot_ind = right;
    }
    else
    {
        swap(right + 1, pivot_ind);
        pivot_ind = right + 1;
    }
    return pivot_ind;
}

int element_number_k(int left, int right, int k)
{
    if (left == right)
    {
        return a[left];
    }
    else
    {
        int place = partition(left, right, right);
        if (place == k)
        {
            return a[place];
        }
        if (k < place)
        {
            element_number_k(left, place - 1, k);
        }
        else
        {
            element_number_k(place + 1, right, k);
        }
    }
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


int main()
{
    read_data_from_stream();
    int k;
    scanf("%d", &k);

    printf("%d", element_number_k(0, n - 1, k));
    return 0;
}

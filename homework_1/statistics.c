#define SIZE 100000
#include<math.h>
#include<stdio.h>


int n;
int a[SIZE];

int minimum()
{
    int res = a[0];
    int i;
    for (i = 0; i < n; ++i)
    {
        if (a[i] < res)
        {
            res = a[i];
        }
    }
    return res;
}


int maximum()
{
    int res = a[0];
    int i;
    for (i = 0; i < n; ++i)
    {
        if (a[i] > res)
        {
            res = a[i];
        }
    }
    return res;
}

double average()
{
    double res = 0;
    int i;
    for (i = 0; i < n; ++i)
    {
        res = res + 1.0 * a[i] / n;
    }
    return res;
}

double dispersion()
{
    double res = 0;
    double m = average();

    int i;
    for (i = 0; i < n; ++i)
    {
        res = res + (a[i] - m) * (a[i] - m) / (n - 1);
    }
    return res;

}

double standard_deviation()
{
    return pow(dispersion(), 0.5);
}


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

int median()
{
    return element_number_k(0, n - 1, n / 2);
}

int deviation_of_maximum_from_the_median()
{
    return (maximum() - median());
}

int deviation_of_minimum_from_the_median()
{
    return (median() - minimum());
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
    printf("minimum: %d\n", minimum());
    printf("maximum: %d\n", maximum());
    printf("average: %lf\n", average());
    printf("dispersion: %lf\n", dispersion());
    printf("standard deviation: %lf\n", standard_deviation());
    printf("deviation of minimum from the median: %d\n", deviation_of_minimum_from_the_median());
    printf("deviation of maximum from the median: %d\n", deviation_of_maximum_from_the_median());

    return 0;
}

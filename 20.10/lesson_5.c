#include<stdio.h>
#include<stdlib.h>

int* shuffle(int a[], int n)
{
    int* a1 = (int*) malloc(n * sizeof(int));
    int i;
    int place;
    for (i = 0; i < n; ++i)
    {
        *(a1 + i) = a[i];
        place = rand() % (i + 1);
        int tmp = *(a1 + place);
        *(a1 + place) = a[i];
        *(a1 + i) = tmp;
    }
    return a1;
}



int main()
{
    int n;
    scanf("%d", &n);
    int a[n];
    int i;
    for (i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
    srand(57);
    int* pointer = shuffle(a, n);
    for (i = 0; i < n; ++i)
    {
        printf("%d ", *(pointer + i));
    }

    return 0;
}

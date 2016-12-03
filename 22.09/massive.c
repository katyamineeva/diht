#define SIZE 1000
#include<stdio.h>

void swap(int* a, int* b)
{
    int c = *a;
    *a = *b;
    *b = c;

}

int main()
{
    int a = 3;
    int b = 7;
    swap(&a, &b);
    printf("a = %d\nb = %d", a, b);
    return 0;
}

#include<stdio.h>
int n_1 = 1;
int n_2 = 1;
int n_3 = 1;


void fibonacci(int n)
{

    int i, tmp;
    for (i = 0; i < (n - 3); ++i)
    {
        tmp = n_1 + n_2 + n_3;
        n_3 = n_2;
        n_2 = n_1;
        n_1 = tmp;
    }
    printf("%d", n_1);
}


int main()
{
    int n;
    scanf("%d", &n);
    fibonacci(n);
    return 0;
}

#include<stdio.h>
int rec_solution = 0;
int true_solution = 1;

int n_1 = 1;
int n_2 = 1;
int n_3 = 1;

int fibonacci_rec(int n)
{
    ++rec_solution;
    if (n < 4)
    {
        return 1;
    }
    else
    {
        return (fibonacci_rec(n - 1) + fibonacci_rec(n - 2) + fibonacci_rec(n - 3));
    }
}


void fibonacci(int n)
{

    int i, tmp;
    for (i = 0; i < (n - 3); ++i)
    {
        ++true_solution;
        tmp = n_1 + n_2 + n_3;
        n_3 = n_2;
        n_2 = n_1;
        n_1 = tmp;
    }
}



int main()
{
    int n;
    scanf("%d", &n);
    int res = fibonacci_rec(n);
    fibonacci(n);

    printf("fibonacci number: %d\n", res);
    printf("amount of actions in recursion solution: %d\n", rec_solution);
    printf("amount of actions in dinamic solution: %d\n", true_solution);
    return 0;
}

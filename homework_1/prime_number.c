#include<stdio.h>

int is_prime(int n)
{
    if (n == 1)
    {
        return 0;
    }

    int flag = 1;
    int i;
    for (i = 2; i * i <= n; ++i)
    {
        if (n % i == 0)
        {
            flag = 0;
            break;
        }
    }
    return flag;
}

int main()
{
    int n;
    scanf("%d", &n);
    if (is_prime(n))
    {
        printf("YES");
    }
    else
    {
        printf("NO");
    }
    return 0;
}

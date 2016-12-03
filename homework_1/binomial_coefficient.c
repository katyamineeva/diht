#include<stdio.h>

long long int c(long long int n, long long int k)
{
    long long int ans = 1;
    long long int i;
    for (i = 1; i <= (n - k); ++i)
    {
        ans = ans * (k + i) / i;
    }
    return ans;
}


int main()
{
    long long int n, k;
    scanf("%lld %lld", &n, &k);

    long long int ans = c(n, k);

    printf("%lld", ans);

    return 0;
}

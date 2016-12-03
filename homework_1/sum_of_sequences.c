#define exact_result 1.64493406685
#include<stdio.h>
#define SIZE1 100000
#define SIZE2 100000000
#define SIZE3 1000000000
#define double float

double summation(long long n)
{
    double res = 0;
    long long i;
    for (i = 1; i <= n; ++i)
    {
        res = res + 1.0 / (i * i);
    }
    return res;
}

double reversed_summation(long long n)
{
    double res = 0;
    long long i;
    for (i = n; i > 0; --i)
    {
        res = res + 1.0 / (i * i);
    }
    return res;
}


 int main()
 {
     double sum = summation(SIZE1);
     double rev_sum = reversed_summation(SIZE1);
     printf("1. For %d :\n\n", SIZE1);
     printf("result of summation in direct order: %.11l\f\n", sum);
     printf("deviation from the exact result: %.11lf\n\n", exact_result - sum);
     printf("result of summation in reversed order: %.11lf\n", rev_sum);
     printf("deviation from the exact result: %.11lf\n\n", exact_result - rev_sum);


     sum = summation(SIZE2);
     rev_sum = reversed_summation(SIZE2);
     printf("2. For %d :\n\n", SIZE2);
     printf("result of summation in direct order: %.11lf\n", sum);
     printf("deviation from the exact result: %.11lf\n\n", exact_result - sum);
     printf("result of summation in reversed order: %.11lf\n", rev_sum);
     printf("deviation from the exact result: %.11lf\n\n", exact_result - rev_sum);

     sum = summation(SIZE3);
     rev_sum = reversed_summation(SIZE3);
     printf("3. For %d :\n\n", SIZE3);
     printf("result of summation in direct order: %.11lf\n", sum);
     printf("deviation from the exact result: %.11lf\n\n", exact_result - sum);
     printf("result of summation in reversed order: %.11lf\n", rev_sum);
     printf("deviation from the exact result: %.11lf\n\n", exact_result - rev_sum);

     return 0;
 }

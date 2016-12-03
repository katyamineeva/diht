#include<stdio.h>
#include<stdlib.h>

long long catalanNumber(int num)
{
    long long* catalan = (long long*) malloc(num * sizeof(long long));
	catalan[0] = 1;
	int i, j;
	for (i = 1; i <= num; i++){
		catalan[i] = 0;
		for (j = 0; j < i; j++)
			catalan[i] += catalan[j] * catalan[i - 1 - j];
	}
	long long res = catalan[num];
	free(catalan);
	return res;
}

int main()
{
	int number, i;
	scanf("%d", &number);
	for (i = 1; i <= number; ++i)
    {
        printf("%ld ", catalanNumber(i));
    }

	return 0;
}

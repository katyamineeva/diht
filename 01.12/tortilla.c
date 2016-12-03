#include<stdio.h>
#define SIZE 1024


int a[SIZE][SIZE];
int m, n;

void ReadData()
{
    FILE* input = fopen("input.txt", "r");
    fscanf(input, "%d %d\n", &m, &n);
    int i, j;
    for (i = 0; i < m; ++i)
    {
        for (j = 0; j < n; ++j)
        {
            fscanf(input, "%d", &a[i][j]);
        }
    }
    fclose(input);
}


int main()
{
    ReadData();
    int i, j;
    for (i = 1; i < m; ++i)
    {
        for (j = 1; j < n; ++j)
        {
            if (a[i - 1][j] > a[i][j - 1])
            {
                a[i][j] = a[i][j] + a[i - 1][j];
            }
            else
            {
                a[i][j] = a[i][j] + a[i][j - 1];
            }
        }
    }
    printf("%d", a[m - 1][n - 1]);

    return 0;
}

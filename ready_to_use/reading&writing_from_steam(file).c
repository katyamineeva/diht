#define SIZE 100000
#include<stdio.h>
#include<stdlib.h>

int a[SIZE];
int n;

void ReadStrings()
{
    FILE* input = fopen("input.txt", "r");
    if (input == NULL)
    {
        printf("input error");
    }
    else
    {
        fscanf(input, "%d", &n1);
        fscanf(input, "%s", s1);

        fscanf(input, "%d", &n2);
        fscanf(input, "%s", s2);
    }
    fclose(input);
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

void write_data_in_stream()
{
    int i;
    for (i = 0; i < n; ++i)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}




void read_data_from_file()
{
    FILE* input = fopen("input.txt", "r");
    if (input == NULL)
    {
        printf("input error");
    }
    else
    {
        fscanf(input, "%d", &n);
        int i;
        for (i = 0; i < n; ++i)
        {
            fscanf(input, "%d", &a[i]);
        }
    }
    fclose(input);
}

void write_data_in_file()
{
    FILE* output = fopen("output.txt", "w");
    int i;
    for (i = 0; i < n; ++i)
    {
        fprintf(output, "%d ", a[i]);
    }
    fclose(output);
}






int main()
{

    return 0;
}

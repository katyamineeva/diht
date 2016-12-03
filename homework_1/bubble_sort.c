#define SIZE 100000
#define MIN_LEN 5
#define MAX_LEN 20
#define MIN_VALUE -57
#define MAX_VALUE 57
#include<stdio.h>
#include<stdlib.h>

int a[SIZE];
int n;

void bubble()
{
    int i, j, tmp;
    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < (n - i - 1); ++j)
        {
            if (a[j] > a[j + 1])
            {
                tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
            }
        }
    }

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



void generate_data()
{
    srand(57);
    n = MIN_LEN + rand() % (MAX_LEN - MIN_LEN);

    int i;
    for (i = 0; i < n; ++i)
    {
        a[i] = MIN_VALUE + rand() % (MAX_VALUE - MIN_VALUE);
    }
}




int main()
{
    read_data_from_stream();
    //read_data_from_file();
    //generate_data();

    bubble();

    write_data_in_stream();
    //write_data_in_file();
    return 0;
}

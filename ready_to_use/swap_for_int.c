void swap(int* x, int* y)
{
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

int main()
{
    int a = 5;
    int b = 7;
    swap(&a, &b);
    printf("%d%d", b, a);
    return 0;
}

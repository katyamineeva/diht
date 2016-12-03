#define MIN_LEN
#define MAX_LEN
#define MIN_VALUE
#define MAX_VALUE

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


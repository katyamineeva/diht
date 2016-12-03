#define SIZE1 256
#define SIZE2 10000
#include<stdio.h>

void print(char**)
{

}

char** split(char* s1, char* s2)
{
    char A[SIZE1][SIZE1];
    int i = 0;
    int j = 0;
    while (s2 != "\n")
    {
        char* tmp1 = s1;
        char* tmp2 = s2;
        while (tmp2 != "\n")
    }


}


int main()
{
    char s1[SIZE1];
    scanf ("%s", s1);
    char s2[SIZE2];
    scanf("%s", s2);

    print(split(s1, s2));

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student
{
    unsigned card;
    char* name;
    short mark;
};

struct student** GetList(unsigned n)
{
    struct student** list = (struct student**) malloc(n * sizeof(struct student*));
    int i;

    for(i = 0; i < n; ++i)
    {
        list[i] = (struct student*)malloc(sizeof(struct student));

        char cur = getchar();
        unsigned card = 0;
        while (cur != ' ')
        {
            card = 10 * card + (cur - '0');
            cur = getchar();
        }
        list[i]->card = card;

        cur = getchar();
        char* name = (char*)malloc(32 * sizeof(char));
        int j = 0;
        while (cur != ' ')
        {
            name[j] = cur;
            ++j;
            cur = getchar();
        }
        name[j] = '\n';
        list[i]->name = name;

        short mark = getchar() - '0';
        list[i]->mark = mark;

        getchar();
    }

    return list;
}

int compStr(char* str1, char* str2){
    unsigned i = 0;
    while (str1[i] != '\n' && str2[i] != '\n')
    {
        if (str1[i] < str2[i])
        {
            return 1;
        }
        else if (str1[i] > str2[i]) return 0;
        ++i;
    }
    if (str1[i] == '\n')
    {
        return 0;
    }
    return 1;
}

void swap(struct student* stud1, struct student* stud2)
{
    struct student temp = *stud1;
    *stud1 = *stud2;
    *stud2 = temp;
}

void sort(struct student** list, int size)
{
    int i;
    for(i = size; i > 0; --i)
    {
        int j;
        for(j = 1; j < i; ++j)
        {
            if(compStr(list[j]->name, list[j-1]->name))
            {
                swap(list[j], list[j-1]);
            }
        }
    }
}

void printList(struct student** list, int n)
{
    int i;
    for (i = 0; i < n; ++i)
    {
        printf("%u ", list[i]->card);

        int j = 0;
        while (list[i]->name[j] != '\n')
        {
            putchar(list[i]->name[j]);
            ++j;
        }

        printf(" %u\n", list[i]->mark);
    }
}

struct student* binSearch(struct student** begin, int r, char* name)
{
    int l = -1;
    while (l != r-1)
    {
        if (compStr(begin[(r + l) / 2]->name, name)) l = (r + l) / 2;
        else r = (r + l) / 2;
    }
    return begin[r];
}

int isEqual(char* str1, char* str2)
{
    int i = 0;
    while (str1[i] != '\n') {
        if (str1[i] != str2[i]) return 0;
        ++i;
    }
    if (str2[i] == '\n')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int studSearch(struct student** list, int n)
{
    char* entered = (char*)malloc(32 * sizeof(char));
    printf("Enter student's name: ");
    char letter = getchar();
    if (letter == '\n')
    {
        return 0;
    }
    int i = 0;
    while (letter != '\n')
    {
        entered[i] = letter;
        ++i;
        letter = getchar();
    }
    entered[i] = letter;
    struct student* searched = binSearch(list, n - 1, entered);
    if (isEqual(searched->name, entered)) printf("student's card number: %u\nmark: %u\n\n", searched->card, searched->mark);
    else printf("No students with this name\n\n");

    return 1;
}

int main(int argc, const char * argv[])
{
    unsigned n;
    scanf("%u ", &n);
    struct student** list = GetList(n);
    sort(list, n);

    printList(list, n);
    while (studSearch(list, n));
    return 0;
}

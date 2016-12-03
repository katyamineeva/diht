#include<stdio.h>
#define MaxLen 32
#define MinMark 2
#define MaxMark 5
typedef struct Student Student;

int n;

struct Student
{
    int Number;
    char Name[MaxLen];
    char SecondName[MaxLen];
    char Surname[MaxLen];
    int Mark;
};

int* CountSort(Student* list)
{
    Student** SortedList = (Student**) malloc(n * sizeof(Student*));
    int size = MaxMark - MinMark + 1;
    int* index = (int*) malloc(size * sizeof(int));
    int i, cnt, tmp, ind;

    for (i = 0; i < size; ++i)
    {
        index[i] = 0;
    }
    for (i = 0; i < n; ++i)
    {
        ++index[list[i].Mark - MinMark];
    }
    cnt = 0;
    for (i = 0; i < size; ++i)
    {
        tmp = index[i];
        index[i] = cnt;
        cnt = cnt + tmp;
    }

    for (i = 0; i < n; ++i)
    {
        ind = index[list[i].Mark - MinMark];
        SortedList[ind] = &list[i];
        ++index[list[i].Mark - MinMark];
    }
    return SortedList;

}

Student* ReadData()
{
    FILE* input = fopen("input.txt", "r");
    fscanf(input, "%d", &n);

    Student* list = (Student*) malloc(n * sizeof(Student));
    int i;
    for (i = 0; i < n; ++i)
    {
        fscanf(input, "%d %s %s %s %d", &list[i].Number, list[i].Name, list[i].SecondName, list[i].Surname, &list[i].Mark);
    }
    fclose(input);
    return list;
}


void WriteData(Student** list)
{
    FILE* output = fopen("output.txt", "w");
    int i;
    for (i = 0; i < n; ++i)
    {
        fprintf(output, "%d %s %d\n", list[i]->Number, list[i]->Name, list[i]->Mark);
    }
    fclose(output);
}

int main()
{
    Student* list = ReadData();
    Student** SortedList = CountSort(list);
    WriteData(SortedList);

    free(list);
    free(SortedList);
    return 0;
}

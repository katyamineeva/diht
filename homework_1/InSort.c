//Сортируем массив строк вставками



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define N 32

void RandArr(char *a, int n);
void InSort(char **a, int sizeArr,  int (*cmp)(const char *, const char *));


int StrCmp(char *a,  char *b) //Функция сравнения 2-х строк без учета регистра
{
	int i = 0;
	char cA, cB;
	while(a[i]!='\0' && b[i]!= '\0')
	{
		cA = tolower(a[i]);
		cB = tolower(b[i]);

		if(cA<cB)
			return -1;
		if(cA>cB)
			return 1;
		i++;
	}
	if(a[i] == '\0' && b[i] != '\0')
		return -1;
	if(a[i] == '\0' && b[i] == '\0')
		return 0;
	if(a[i] != '\0' && b[i] != '\0')
		return 1;
} 

void RandArr(char *a, int n)  //Функция получения случайной строки
{
	int i, r;
	
	for(i=0; i<n; i++)
		a[i] = rand()%74 + 48;
	return;
} 

void InSort(char **a, int sizeArr,  int (*cmp)(char *, char *)) //Сортировка вставками
{
	char *temp = (char*)malloc(sizeArr*sizeof(char));
	int i, j;

		
	for (i = 1; i < sizeArr; i++)
	{
		temp = a[i];
		for (j = i - 1; j >= 0; j--)
		{
			if ((*cmp)(a[j], temp)<0)
				break;
 
			a[j + 1] = a[j];
			a[j] = temp;
		}
	}

}

void main()
{
	
	int i, n, size;
	char **a;

	int (*p)(char *, char *);
	p = StrCmp;

	scanf("%d", &n);
	a = (char**)malloc(n*sizeof(char*));
	
	srand(1024);	
	for(i=0; i<n; i++)
	{
		size = rand()%12 + 20;
		a[i] = (char*)malloc(size*sizeof(char));	
		RandArr(a[i], size);
		a[i][size] = '\0';
		printf("%d\n", size);
	}
	

	for(i = 0; i < n; i++)
		printf("%s\n", a[i]);
	printf("\n");


	InSort(a, n, p);
	for(i = 0; i < n; i++)
		printf("%s\n", a[i]);

	scanf("%d");
	free(a);
	return;

}

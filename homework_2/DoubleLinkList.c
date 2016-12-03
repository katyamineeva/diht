#include<stdio.h>
#include<stdlib.h>
typedef struct Node Node;

struct Node
{
    Node* prev;
    Node* next;
    int value;
};

typedef struct
{
    Node* first;
    Node* last;
    int length;
} List;

List* createList()
{
    List* mylist = (List*) malloc(sizeof(List));
    mylist->first = NULL;
    mylist->last = NULL;
    mylist->length = 0;
    return mylist;
}

Node* createNode(Node* prev_, Node* next_, int value_)
{
    Node* tmp = (Node*) malloc(sizeof(Node));
    tmp->prev = prev_;
    tmp->next = next_;
    tmp->value = value_;

    return tmp;
}

int pushBack(List* mylist, int elem)
{

    if (mylist->length == 0)
    {
        mylist->first = createNode(NULL, NULL, elem);
        mylist->last = mylist->first;
        ++mylist->length;
    }
    else
    {
         mylist->last->next = createNode(mylist->last, NULL, elem);
         mylist->last = mylist->last->next;
         ++mylist->length;
    }

    if (mylist->last == NULL)
    {
        return 0;
    }
    return 1;
}

int pushFront(List* mylist, int elem)
{

    if (mylist->length == 0)
    {
        mylist->first = createNode(NULL, NULL, elem);
        mylist->last = mylist->first;
        ++mylist->length;
    }
    else
    {
        mylist->first->prev = createNode(NULL, mylist->first, elem);
        mylist->first = mylist->first->prev;
        ++mylist->length;
    }

    if (mylist->first == NULL)
    {
        return 0;
    }
    return 1;

}

int popBack(List* mylist, int* x)
{
    if (mylist->length <= 1)
    {
        if (mylist->length == 1)
        {
            *x = mylist->last->value;
            free(mylist->last);
            --mylist->length;
            mylist->first = mylist->last = NULL;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        *x = mylist->last->value;
        mylist->last = mylist->last->prev;
        free(mylist->last->next);
        mylist->last->next = NULL;
        --mylist->length;
    }
    return 1;
}

int popFront(List* mylist, int* x)
{
    if (mylist->length <= 1)
    {
        if (mylist->length == 1)
        {
            *x = mylist->first->value;
            free(mylist->first);
            --mylist->length;
            mylist->first = mylist->last = NULL;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        *x = mylist->first->value;
        mylist->first = mylist->first->next;
        free(mylist->first->prev);
        mylist->first->prev = NULL;
        --mylist->length;
    }
    return 1;
}

void deleteNodes(Node* curNode)
{
    if (curNode->next != NULL)
    {
        deleteNodes(curNode->next);
    }
    free(curNode);
}

int deleteList(List* mylist)
{
    if (mylist == NULL)
    {
        return 0;
    }

    if (mylist)
    {

        if (mylist->first)
        {
            deleteNodes(mylist->first);
        }
        free(mylist);
    }
    return 1;
}



void printNodes(Node* curNode)
{
    while (curNode)
    {
        printf("%d ", curNode->value);
        curNode = curNode->next;
    }
    printf("\n");
}

void printList(List* mylist)
{
    printNodes(mylist->first);
}


void someTests(List* mylist)
{
    int x;
    if (pushFront(mylist, 5))
    {
        printList(mylist);
    }
    else
    {
        printf("error\n");
    }

    if (pushBack(mylist, 7))
    {
        printList(mylist);
    }
    else
    {
        printf("error\n");
    }

    if (popFront(mylist, &x))
    {
        printList(mylist);
    }
    else
    {
        printf("error\n");
    }

    if (popBack(mylist, &x))
    {
        printList(mylist);
    }
    else
    {
        printf("error\n");
    }
    if (popFront(mylist, &x))
    {
        printList(mylist);
    }
    else
    {
        printf("error\n");
    }
    if (pushFront(mylist, 1))
    {
        printList(mylist);
    }
    else
    {
        printf("error\n");
    }

}

void swapForChar(char* x, char* y)
{
    char tmp = *x;
    *x = *y;
    *y = tmp;
}

void swap(void* x, void* y, size_t size)
{
    char* x1 = (char*) x;
    char* y1 = (char*) y;
    int i;
    for (i = 0; i < size; ++i)
    {
        swapForChar(x1 + i, y1 + i);
    }
    x = (void*) x1;
    y = (void*) y1;
}


int main()
{
    List* mylist = createList();
    someTests(mylist);
    deleteList(mylist);
    return 0;
}

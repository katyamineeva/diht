#include "stack.h"
//#define SIZE 50
//typedef struct Stack Stack;


Stack* getNewStack()
{
    Stack* myStack = (Stack*) malloc(sizeof(Stack));
    myStack->elements = (char*) malloc(SIZE * sizeof(char));
    myStack->size = 0;
    myStack->maxSize = SIZE;
    return myStack;
}

void deleteStack(Stack* myStack)
{
    free(myStack->elements);
    free(myStack);
}

char look(Stack* myStack)
{
    if (myStack->size == 0)
    {
        printf("error");
    }
    else
    {
        return myStack->elements[myStack->size - 1];
    }
}

void push(Stack* myStack, char elem)
{
    if (myStack->size >= myStack->maxSize)
    {
        myStack->maxSize = myStack->maxSize * 2;
        myStack->elements = (char*) realloc(myStack->elements, myStack->maxSize * sizeof(char));
    }
    myStack->elements[myStack->size] = elem;
    ++myStack->size;
}

void pop(Stack* myStack)
{
    if (myStack->size == 0)
    {
        printf("error");
    }
    else
    {
        --myStack->size;
        if (myStack->size * 4 < myStack->maxSize)
        {
            myStack->maxSize = myStack->maxSize / 2;
            myStack->elements = (char*) realloc(myStack->elements, myStack->maxSize * sizeof(char));
        }
    }
}

#define SIZE 50
#include<stdlib.h>
#include<stdio.h>

char* stack;
int length = 0;
int size = 50;



void increase_size()
{
    size = size * 2;
    stack = (char*) realloc(stack, size);
    if (stack == NULL)
    {
        printf("error");
    }
}

void decrease_size()
{
    size = size / 2;
    stack = (char*) realloc(stack, size);
}


char top()
{
    return *(stack + length - 1);
}

void pop()
{
    --length;
}

void push(char c)
{
    *(stack + length) = c;
    ++length;
}

int empty_stack()
{
    if (length == 0)
    {
        return 1;
    }
    return 0;
}

int full_stack()
{
    if (length < size - 1)
    {
        return 0;
    }
    return 1;
}

int size_too_big()
{
    if (length * 4 < size)
    {
        return 1;
    }
    return 0;
}



int is_opening_bracket(char c)
{
    if (c == '(' || c == '{' || c == '[' || c == '<')
        {
            return 1;
        }
    return 0;
}

char is_opening_bracket(char c)
{
    if (c == ')')
    {
        return '(';
    }
    if (c == ']')
    {
        return '[';
    }
    if (c == '}')
    {
        return '{';
    }
    return '<';
}



int check()
{
    char bracket;
    while ((bracket = getchar()) != '\n' && bracket != EOF)
    {
        if (is_opening_bracket(bracket))
        {
            if (full_stack())
            {
                increase_size();
            }
            push(bracket);
        }
        else
        {
            if (empty_stack())
            {
                return 0;
            }
            if (top() == get_pair_bracket(bracket))
            {
                pop();
            }
            else
            {
                return 0;
            }

            if (size_too_big())
            {
                decrease_size();
            }
        }
    }

    if (length == 0)
    {
        return 1;
    }
    return 0;
}


int main()
{
    stack = (char*) malloc(SIZE * sizeof(char));
    if (check())
    {
        printf("YES");
    }
    else
    {
        printf("NO");
    }
    free(stack);

    return 0;
}

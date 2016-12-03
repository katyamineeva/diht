#include<stdio.h>
#include<stdlib.h>
#include "stack.h"

int isOperator(char symbol)
{
    if (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/')
    {
        return 1;
    }
    return 0;
}

int isOpeningBracket(char symbol)
{
    if (symbol == '(')
    {
        return 1;
    }
    return 0;
}

int isClosingBracket(char symbol)
{
    if (symbol == ')')
    {
        return 1;
    }
    return 0;
}

int isNumber(char symbol)
{
    if ('0' <= symbol && symbol <= '9')
    {
        return 1;
    }
    return 0;
}

int getResult(int operand1, int operand2, char operator)
{
    if (operator == '/')
    {
        return operand2 / operand1;
    }
    if (operator == '*')
    {
        return operand1 * operand2;
    }
    if (operator == '-')
    {
        return operand2 - operand1;
    }
    return operand1 + operand2;
}

int getInt(char c)
{
    return (int)(c - '0');
}

int calculate(char* rpn)
{
    Stack* myStack = getNewStack(sizeof(int));
    int res, operand1, operand2;
    int* number;
    int* result;
    int i = 0;
    while (rpn[i] != '\0')
    {
        number = (int*) malloc(sizeof(int));
        *number = 0;

        if (rpn[i] == ' ')
        {
            ++i;
        }

        if (isNumber(rpn[i]))
        {
            while (isNumber(rpn[i]))
            {
                *number = *number * 10 + getInt(rpn[i]);
                ++i;
            }
            push(myStack, number);
        }
        if (isOperator(rpn[i]))
        {
            if (myStack->size < 2)
            {
                printf("error");
            }
            else
            {
                operand1 = *(int*)look(myStack);
                pop(myStack);
                operand2 = *(int*)look(myStack);
                pop(myStack);

                result = (int*) malloc(sizeof(int));
                *result = getResult(operand1, operand2, rpn[i]);
                push(myStack, result);
                ++i;
            }
        }
    }
    int ans = *(int*)look(myStack);
    free(myStack->elements);
    free(myStack);

    return ans;
}

char* rpn(char* infixNotation, int length)
{
    Stack* myStack = getNewStack(sizeof(char));
    char* postfixNotation = (char*) malloc((length + 1) * sizeof(char));
    int rpnInd = 0;
    char* curSymbol;

    int infixNotInd;
    for (infixNotInd = 0; infixNotInd < length; ++infixNotInd)
    {
        curSymbol = &infixNotation[infixNotInd];

        if (isNumber(*curSymbol))
        {
            postfixNotation[rpnInd] = *curSymbol;
            ++rpnInd;
        }

        if (*curSymbol == ' ' && rpnInd > 0 && postfixNotation[rpnInd - 1] != ' ')
        {
            postfixNotation[rpnInd] = *curSymbol;
            ++rpnInd;
        }

        if (isOperator(*curSymbol) || isOpeningBracket(*curSymbol))
        {
            push(myStack, curSymbol);
        }
        if (isClosingBracket(*curSymbol))
        {
            while (myStack->size > 0 && !isOpeningBracket(*(char*)look(myStack)))
            {
                postfixNotation[rpnInd] = ' ';
                ++rpnInd;
                postfixNotation[rpnInd] = *(char*)look(myStack);
                ++rpnInd;
                pop(myStack);
            }
            pop(myStack);
        }
    }
    while (myStack->size > 0)
    {
        postfixNotation[rpnInd] = ' ';
        ++rpnInd;

        postfixNotation[rpnInd] = *(char*)look(myStack);
        ++rpnInd;
        pop(myStack);
    }
    postfixNotation[rpnInd] = '\0';
    deleteStack(myStack);

    return postfixNotation;
}

char* readData(int* length)
{
    FILE* input = fopen("input.txt", "r");

    int curSize = 0;
    char* str = (char*) malloc(SIZE * sizeof(char));
    int maxSize = SIZE;
    char symbol = fgetc(input);

    while (symbol != '\n')
    {
        if (curSize + 1 >= maxSize)
        {
            maxSize = maxSize * 2;
            str = (char*) realloc(str, maxSize * sizeof(char));
        }
        str[curSize] = symbol;
        symbol = fgetc(input);
        ++curSize;
    }
    str[curSize] = '\0';
    *length = curSize;

    fclose(input);
    return str;
}

int main()
{
    int length;
    char* infixNotation = readData(&length);

    char* postfixNotation = rpn(infixNotation, length);
    printf("reverse polish notation: %s\n", postfixNotation);
    int res = calculate(postfixNotation);
    printf("result: %d\n", res);

    free(postfixNotation);
    free(infixNotation);
    return 0;
}

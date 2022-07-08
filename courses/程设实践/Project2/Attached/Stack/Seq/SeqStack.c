#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "SeqStack.h"

void init(SeqStack *pStack)
{
    assert(pStack != NULL);
    pStack->data = (DataType *)malloc(STANDARDSIZE * sizeof(DataType));
    assert(pStack->data != NULL);
    pStack->top = BOTTOM;
    pStack->size = STANDARDSIZE;
}

void clear(SeqStack *pStack)
{
    assert(pStack != NULL);
    pStack->top = BOTTOM;
}

void destroy(SeqStack *pStack)
{
    assert(pStack != NULL);
    clear(pStack);
    free(pStack->data);
    pStack->data = NULL;
    pStack->size = 0;
}

int isEmpty(SeqStack *pStack)
{
    assert(pStack != NULL);
    return pStack->top == BOTTOM;
}

int getSize(SeqStack *pStack)
{
    assert(pStack != NULL);
    return pStack->top - BOTTOM;
}

int isFull(SeqStack *pStack)
{
    assert(pStack != NULL);
    return getSize(pStack) == pStack->size;
}

void append(SeqStack *pStack)
{
    assert(pStack != NULL);
    DataType *temp = (DataType *)realloc(pStack->data, (pStack->size + STANDARDSIZE) * sizeof(DataType));
    assert(temp != NULL);
    pStack->data = temp;
    pStack->size += STANDARDSIZE;
}

void push(SeqStack *pStack, DataType e)
{
    assert(pStack != NULL);
    if (isFull(pStack))
    {
        append(pStack);
    }
    pStack->top++;
    pStack->data[pStack->top] = e;
}

void pop(SeqStack *pStack)
{
    assert(pStack != NULL);
    if (isEmpty(pStack))
    {
        printf("Error! It is Empty");
        exit(1);
    }
    pStack->top--;
}

DataType getTopData(SeqStack *pStack)
{
    assert(pStack != NULL);
    if (isEmpty(pStack))
    {
        printf("Error! It is Empty");
        exit(1);
    }
    return pStack->data[pStack->top];
}

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "LinkStack.h"

void init(LinkStack *pStack)
{
    assert(pStack != NULL);
    pStack->top = (LinkStackNode *)malloc(sizeof(LinkStackNode));
    assert(pStack->top != NULL);
    pStack->top->next = BOTTOM;
    pStack->size = 0;
}

void clear(LinkStack *pStack)
{
    while (pStack->top->next != BOTTOM)
    {
        Position temp = pStack->top->next;
        pStack->top->next = temp->next;
        free(temp);
        temp = NULL;
    }
}

void destroy(LinkStack *pStack)
{
    assert(pStack != NULL);
    clear(pStack);
    free(pStack->top);
    pStack->top = NULL;
}

int isEmpty(LinkStack *pStack)
{
    assert(pStack != NULL);
    return pStack->top->next == BOTTOM;
}

int getSize(LinkStack *pStack)
{
    assert(pStack != NULL);
    return pStack->size;
}

void push(LinkStack *pStack, DataType e)
{
    assert(pStack != NULL);
    LinkStackNode *pNew = (LinkStackNode *)malloc(sizeof(LinkStackNode));
    assert(pNew != NULL);
    pNew->data = e;
    pNew->next = pStack->top->next;
    pStack->top->next = pNew;
    pStack->size++;
}

void pop(LinkStack *pStack)
{
    assert(pStack != NULL);
    Position temp = pStack->top->next;
    assert(temp != BOTTOM);
    pStack->top->next = temp->next;
    free(temp);
    temp = NULL;
    pStack->size--;
}

DataType getTopData(LinkStack *pStack)
{
    assert(pStack != NULL);
    Position temp = pStack->top->next;
    assert(temp != BOTTOM);
    return temp->data;
}

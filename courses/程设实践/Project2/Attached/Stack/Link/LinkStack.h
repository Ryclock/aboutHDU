#ifndef _LINKSTACK_H_INCLUDED_
#define _LINKSTACK_H_INCLUDED_

#define BOTTOM NULL

typedef int DataType;

typedef struct Node
{
    struct Node *next;
    DataType data;
} LinkStackNode, *Position;

typedef struct
{
    Position top;
    int size;
} LinkStack;

void init(LinkStack *pStack);

void clear(LinkStack *pStack);

void destroy(LinkStack *pStack);

int isEmpty(LinkStack *pStack);

int getSize(LinkStack *pStack);

void push(LinkStack *pStack, DataType e);

void pop(LinkStack *pStack);

DataType getTopData(LinkStack *pStack);

#endif
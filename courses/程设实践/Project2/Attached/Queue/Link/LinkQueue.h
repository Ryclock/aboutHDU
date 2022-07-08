#ifndef _SEQSTACK_H_INCLUDED_
#define _SEQSTACK_H_INCLUDED_

typedef int DataType;

typedef struct Node
{
    DataType data;
    struct Node *next;
} LinkQueueNode, *Position;

typedef struct
{
    Position front;
    Position rear;
    int size;
} LinkQueue;

void init(LinkQueue *pQueue);

void clear(LinkQueue *pQueue);

void destroy(LinkQueue *pQueue);

int isEmpty(LinkQueue *pQueue);

int getSize(LinkQueue *pQueue);

void push(LinkQueue *pQueue, DataType e);

void pop(LinkQueue *pQueue);

DataType getTopData(LinkQueue *pQueue);

#endif
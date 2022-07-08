#ifndef _SEQSTACK_H_INCLUDED_
#define _SEQSTACK_H_INCLUDED_

#define STANDARDSIZE 4

typedef int DataType;

typedef DataType *Position;

typedef struct
{
    DataType *data;
    int bufferSize;
    int front;
    int rear;
} SeqQueue;

void init(SeqQueue *pQueue);

void clear(SeqQueue *pQueue);

void destroy(SeqQueue *pQueue);

int isEmpty(SeqQueue *pQueue);

int getSize(SeqQueue *pQueue);

int isFull(SeqQueue *pQueue);

void append(SeqQueue *pQueue);

void push(SeqQueue *pQueue, DataType e);

void pop(SeqQueue *pQueue);

DataType getTopData(SeqQueue *pQueue);

#endif
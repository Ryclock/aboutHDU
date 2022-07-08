#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "SeqQueue.h"

void init(SeqQueue *pQueue)
{
    assert(pQueue != NULL);
    pQueue->data = (DataType *)malloc(STANDARDSIZE * sizeof(DataType));
    assert(pQueue->data != NULL);
    pQueue->bufferSize = STANDARDSIZE;
    pQueue->front = pQueue->rear = 0;
}

void clear(SeqQueue *pQueue)
{
    assert(pQueue != NULL);
    pQueue->bufferSize = 0;
    pQueue->front = pQueue->rear = 0;
}

void destroy(SeqQueue *pQueue)
{
    assert(pQueue != NULL);
    clear(pQueue);
    free(pQueue->data);
}

int isEmpty(SeqQueue *pQueue)
{
    assert(pQueue != NULL);
    return pQueue->front == pQueue->rear;
}

int getSize(SeqQueue *pQueue)
{
    assert(pQueue != NULL);
    return (pQueue->rear + pQueue->bufferSize - pQueue->front) % pQueue->bufferSize;
}

int isFull(SeqQueue *pQueue)
{
    assert(pQueue != NULL);
    return (pQueue->rear + 1) % pQueue->bufferSize == pQueue->front;
}

void append(SeqQueue *pQueue)
{
    assert(pQueue != NULL);
    DataType *temp = (DataType *)realloc(pQueue->data, (pQueue->bufferSize + STANDARDSIZE) * sizeof(DataType));
    assert(temp != NULL);
    pQueue->data = temp;
    pQueue->bufferSize += STANDARDSIZE;
}

void push(SeqQueue *pQueue, DataType e)
{
    assert(pQueue != NULL);
    if (isFull(pQueue))
    {
        append(pQueue);
    }
    pQueue->data[pQueue->rear] = e;
    pQueue->rear = (pQueue->rear + 1) % pQueue->bufferSize;
}

void pop(SeqQueue *pQueue)
{
    assert(pQueue != NULL);
    if (isEmpty(pQueue))
    {
        printf("Error! It is Empty");
        exit(1);
    }
    pQueue->front = (pQueue->front + pQueue->bufferSize + 1) % pQueue->bufferSize;
}

DataType getTopData(SeqQueue *pQueue)
{
    assert(pQueue != NULL);
    if (isEmpty(pQueue))
    {
        printf("Error! It is Empty");
        exit(1);
    }
    return pQueue->data[pQueue->front];
}

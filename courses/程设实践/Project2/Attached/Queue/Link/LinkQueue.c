#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "LinkQueue.h"

void init(LinkQueue *pQueue)
{
    assert(pQueue != NULL);
    pQueue->front = (LinkQueueNode *)malloc(sizeof(LinkQueueNode));
    assert(pQueue->front != NULL);
    pQueue->front->next = NULL;
    pQueue->rear = pQueue->front;
    pQueue->size = 0;
}

void clear(LinkQueue *pQueue)
{
    assert(pQueue != NULL);
    while (pQueue->front->next != NULL)
    {
        Position temp = pQueue->front->next;
        temp->data = 0;
        pQueue->front->next = temp->next;
    }
    pQueue->rear = pQueue->front;
    pQueue->size = 0;
}

void destroy(LinkQueue *pQueue)
{
    assert(pQueue != NULL);
    clear(pQueue);
    free(pQueue->front);
    pQueue->front = pQueue->rear = NULL;
}

int isEmpty(LinkQueue *pQueue)
{
    assert(pQueue != NULL);
    return pQueue->front->next == NULL;
}

int getSize(LinkQueue *pQueue)
{
    assert(pQueue != NULL);
    return pQueue->size;
}

void push(LinkQueue *pQueue, DataType e)
{
    assert(pQueue != NULL);
    LinkQueueNode *pNew = (LinkQueueNode *)malloc(sizeof(LinkQueueNode));
    assert(pNew != NULL);
    pNew->data = e;
    pNew->next = pQueue->rear->next;
    pQueue->rear->next = pNew;
    pQueue->rear = pNew;
    pQueue->size++;
}

void pop(LinkQueue *pQueue)
{
    assert(pQueue != NULL);
    if (isEmpty(pQueue))
    {
        printf("Error! It is Empty");
        exit(1);
    }
    Position temp = pQueue->front->next;
    pQueue->front->next = temp->next;
    if (temp == pQueue->rear)
    {
        pQueue->rear = pQueue->front;
    }
    pQueue->size--;
}

DataType getTopData(LinkQueue *pQueue)
{
    assert(pQueue != NULL);
    if (isEmpty(pQueue))
    {
        printf("Error! It is Empty");
        exit(1);
    }
    Position temp = pQueue->front->next;
    return temp->data;
}

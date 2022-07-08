#ifndef _SEQSTACK_H_INCLUDED_
#define _SEQSTACK_H_INCLUDED_

#define STANDARDSIZE 4
#define BOTTOM -1

typedef int DataType;

typedef DataType *Position;

typedef struct
{
    DataType *data;
    int top;
    int size;
} SeqStack;

void init(SeqStack *pStack);

void clear(SeqStack *pStack);

void destroy(SeqStack *pStack);

int isEmpty(SeqStack *pStack);

int getSize(SeqStack *pStack);

int isFull(SeqStack *pStack);

void append(SeqStack *pStack);

void push(SeqStack *pStack, DataType e);

void pop(SeqStack *pStack);

DataType getTopData(SeqStack *pStack);

#endif
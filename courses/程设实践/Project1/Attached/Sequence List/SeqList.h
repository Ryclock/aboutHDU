#ifndef _SEQLIST_H_INCLUDED_
#define _SEQLIST_H_INCLUDED_

typedef int listData;
typedef listData *position;

typedef struct seqList
{
    listData *pData;
    int listLength;
    int bufferSize;
} seqList;

typedef struct result1
{
    seqList list;
    listData dataOperated;
    int parametersForJudging;
} resultOfOperateList;

seqList createList(int bufferSize);

void clearList(seqList *pList);

void destroyList(seqList *pList);

resultOfOperateList copyList(seqList *pOldList);

int isEmpty(seqList *pList); // value 1 returned indicates that the sequence list is empty.

int getLength(seqList *pList);

listData *getBeginPosition(seqList *pList);

listData *getEndPosition(seqList *pList);

listData *getNextPosition(position pos);

listData *getPosition(seqList *pList, int order);

listData *locateElement(seqList *pList, listData element);

listData getElement(position pos);

void setElement(seqList *pList, position pos, listData element);

int insertBefore(seqList *pList, position pos, listData element);

resultOfOperateList deleteElement(seqList *pList, position pos);

#endif

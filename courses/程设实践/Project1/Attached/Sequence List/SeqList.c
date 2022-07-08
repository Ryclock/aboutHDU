#include <stdio.h>
#include <stdlib.h>
#include "SeqList.h"

seqList createList(int bufferSize)
{
    seqList list;
    list.pData = (listData *)calloc(bufferSize, sizeof(listData));
    list.listLength = 0;
    list.bufferSize = bufferSize;
    if (list.pData == NULL)
    {
        list.bufferSize = 0;
    }
    return list;
}

void clearList(seqList *pList)
{
    pList->listLength = 0;
}

void destroyList(seqList *pList)
{
    clearList(pList);
    free(pList->pData);
    pList->pData = NULL;
    pList->bufferSize = 0;
}

resultOfOperateList copyList(seqList *pOldList)
{
    resultOfOperateList copyResult;
    copyResult.list = createList(pOldList->bufferSize);
    for (int i = 0; i < pOldList->listLength; i++)
    {
        copyResult.list.pData[i] = pOldList->pData[i];
    }
    copyResult.list.listLength = pOldList->listLength;
    copyResult.parametersForJudging = 0;
    return copyResult;
}

int isEmpty(seqList *pList)
{
    if ((pList->pData != NULL) &&
        (pList->listLength == 0) &&
        (pList->bufferSize != 0))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int getLength(seqList *pList)
{
    return pList->listLength;
}

position getBeginPosition(seqList *pList)
{
    return pList->pData;
}

position getEndPosition(seqList *pList)
{
    return getBeginPosition(pList) + getLength(pList);
}

position getNextPosition(position pos)
{
    return pos + 1;
}

position getPosition(seqList *pList, int order)
{
    if ((order >= 1) && (order <= getLength(pList)))
    {
        return getBeginPosition(pList) + order - 1;
    }
    return getEndPosition(pList);
}

position locateElement(seqList *pList, listData element)
{
    for (position i = getBeginPosition(pList); i < getEndPosition(pList); i = getNextPosition(i))
    {
        if (element == *i)
        {
            return i;
        }
    }
    return getEndPosition(pList);
}

listData getElement(position pos)
{
    return *pos;
}

void setElement(seqList *pList, position pos, listData element)
{
    *pos = element;
}

int insertBefore(seqList *pList, position pos, listData element)
{
    if (getLength(pList) == pList->bufferSize)
    {
        seqList newList = createList(pList->bufferSize * 2);
        pos = pos - getBeginPosition(pList) + getBeginPosition(&newList);
        for (position i = getBeginPosition(pList), posDataInNewList = getBeginPosition(&newList);
             i < getEndPosition(pList);
             i = getNextPosition(i), posDataInNewList++)
        {
            *posDataInNewList = *i;
        }
        newList.listLength = pList->listLength;
        destroyList(pList);
        *pList = newList;
    }
    for (position i = getEndPosition(pList); i > pos; i--)
    {
        *i = *(i - 1);
    }
    *pos = element;
    pList->listLength += 1;
    return 0;
}

resultOfOperateList deleteElement(seqList *pList, position pos)
{
    resultOfOperateList deleteResult;
    if (pos == getEndPosition(pList))
    {
        deleteResult.parametersForJudging = 1;
    }
    else
    {
        deleteResult.dataOperated = getElement(pos);
        while (pos != getEndPosition(pList))
        {
            *pos = *getNextPosition(pos);
            pos = getNextPosition(pos);
        }
        if (pos == getEndPosition(pList))
        {
            pList->listLength -= 1;
            deleteResult.parametersForJudging = 0;
        }
        else
        {
            deleteResult.parametersForJudging = 1;
        }
    }
    return deleteResult;
}

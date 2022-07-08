#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "LinkList.h"

linkList create(void)
{
    linkList list;
    list.pHead = list.pTail = (Node *)malloc(sizeof(Node));
    if (list.pHead != NULL)
    {
        list.pHead->next = NULL;
    }
    return list;
}

void clear(linkList *pList)
{
    position pos = pList->pHead->next;
    while (pos != NULL)
    {
        position temp = pos;
        pos = pos->next;
        free(temp);
    }
    pList->pHead->next = NULL;
    pList->pTail = pList->pHead;
}

void destroy(linkList *pList)
{
    clear(pList);
    free(pList->pHead);
    pList->pHead = pList->pTail = NULL;
}

linkList copy(linkList *pList)
{
    linkList newList;
    newList = create();
    if (newList.pHead != NULL)
    {
        position pos = pList->pHead->next;
        while (pos != NULL)
        {
            Node *pNewNode = (Node *)malloc(sizeof(Node));
            if (pNewNode == NULL)
            {
                destroy(&newList);
                break;
            }
            else
            {
                pNewNode->data = pos->data;
                pNewNode->next = NULL;
                newList.pTail->next = pNewNode;
                newList.pTail = pNewNode;
                pos = pos->next;
            }
        }
    }
    return newList;
}

int isEmpty(linkList *pList)
{
    return (pList->pHead->next == NULL);
}

int getLength(linkList *pList)
{
    int count = 0;
    position pos = pList->pHead->next;
    while (pos != NULL)
    {
        count++;
        pos = pos->next;
    }
    return count;
}

position getBeginPosition(linkList *pList)
{
    return pList->pHead;
}

position getEndPosition(linkList *pList)
{
    return pList->pTail;
}

position getNextPosition(position pos)
{
    return pos->next;
}

position getElementPosition(linkList *pList, listData element)
{
    position pos = pList->pHead->next;
    while (pos != NULL)
    {
        if (pos->data == element)
        {
            return pos;
        }
        pos = getNextPosition(pos);
    }
}

position getPosition(linkList *pList, int serialNumber)
{
    position pos = pList->pHead;
    for (int i = 1; i <= serialNumber; i++)
    {
        pos = pos->next;
    }
    return pos;
}

listData getElement(position pos)
{
    return pos->data;
}

void setElement(position pos, listData element)
{
    pos->data = element;
}

int insertBefore(linkList *pList, position pos, listData element) // return value 0 mean something wrong.
{
    Node *pNewNode = (Node *)malloc(sizeof(Node));
    if (pNewNode != NULL)
    {
        pNewNode->data = element;
        pNewNode->next = pos->next;
        pos->next = pNewNode;
        if (pList->pTail == pos)
        {
            pList->pTail = pNewNode;
        }
        return 1;
    }
    return 0;
}

void deleteElement(linkList *pList, position pos)
{
    position prePos = getPrePosition(pList, pos);
    prePos->next = pos->next;
    if (pList->pTail == pos)
    {
        pList->pTail = prePos;
    }
    free(pos);
}

position getPrePosition(linkList *pList, position pos)
{
    position temp = getBeginPosition(pList);
    position prePos;
    while ((temp != pos) && (temp != NULL))
    {
        prePos = temp;
        temp = getNextPosition(temp);
    }
    return prePos;
}

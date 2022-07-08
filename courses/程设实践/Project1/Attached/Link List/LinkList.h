#ifndef _LINKLIST_H_INCLUDED_
#define _LINKLIST_H_INCLUDED_

typedef int listData;

typedef struct node
{
    listData data;
    struct node *next;
} Node;

typedef Node *position;

typedef struct list
{
    position pHead;
    position pTail;
} linkList;

linkList create(void);

void clear(linkList *pList);

void destroy(linkList *pList);

linkList copy(linkList *pList);

int isEmpty(linkList *pList);

int getLength(linkList *pList);

position getBeginPosition(linkList *pList);

position getEndPosition(linkList *pList);

position getNextPosition(position pos);

position getElementPosition(linkList *pList, listData element);

int getSerialNumber(linkList *pList, position pos);

position getPosition(linkList *pList, int serialNumber);

listData getElement(position pos);

void setElement(position pos, listData element);

int insertBefore(linkList *pList, position pos, listData element);

void deleteElement(linkList *pList, position pos);

position getPrePosition(linkList *pList, position pos);

#endif

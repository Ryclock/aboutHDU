#include <stdio.h>
#include "SeqList.h"

int print_List(seqList *pList)
{
    printf("{");
    for (position i = getBeginPosition(pList); i != getEndPosition(pList); i = getNextPosition(i))
    {
        printf("%d,", getElement(i));
    }
    printf("EndPosition}\n");
    return 0;
}

int main(void)
{
    seqList list = createList(1);
    print_List(&list);
    for (int i = 1; i <= 5; i++)
    {
        insert_Before(&list, getEndPosition(&list), i);
    }
    printList(&list);
    position pos = locateElement(&list, 3);
    if (pos != getEndPosition(&list))
    {
        deleteElement(&list, pos);
    }
    insertBefore(&list, getBeginPosition(&list), 8);
    printList(&list);
    destroyList(&list);
    system("pause");
    return 0;
}
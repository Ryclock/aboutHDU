#include <stdio.h>
#include <stdlib.h>
#include "LinkList.h"

int print(linkList *pList)
{
    printf("{");
    position pos = getBeginPosition(pList);
    while (pos != getEndPosition(pList))
    {
        printf("%d,", getElement(pos->next));
        pos = getNextPosition(pos);
    }
    printf("EndPosition}\n");
    return 0;
}

int main(void)
{
    linkList list = create();
    print(&list);
    for (int i = 1; i <= 5; i++)
    {
        insertBefore(&list, getEndPosition(&list), i);
    }
    print(&list);
    position pos = getElementPosition(&list, 3);
    if (pos != getEndPosition(&list))
    {
        deleteElement(&list, pos);
    }
    insertBefore(&list, getBeginPosition(&list), 8);
    print(&list);
    destroy(&list);
    system("pause");
    return 0;
}

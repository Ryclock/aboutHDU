#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../Attached/Sequence List/SeqList.h"
#include "Others.h"

#define SIZE 60
#define random(x) rand() % (x)

int isCorrect(int procedure)
{
    if (procedure == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int inputChoice(void)
{
    int choice;
    printf("\n\tPlease choose one number : ");
    fflush(stdin);
    scanf("%d", &choice);
    printf("\n");
    return choice;
}

void switchlanguage(char *pLanguage)
{
    if ('C' == *pLanguage)
    {
        *pLanguage = 'E';
    }
    else
    {
        *pLanguage = 'C';
    }
}

void create(seqList *pList)
{
    *pList = createList(SIZE);
    srand(time(0));
    for (int i = 0; i < SIZE; i++)
    {
        insertBefore(pList, getEndPosition(pList), random(100));
    }
}

void printList(seqList *pList)
{
    printf("\n");
    if (isEmpty(pList))
    {
        printf("The sequence is empty");
    }
    else
    {
        for (position i = getBeginPosition(pList); i != getEndPosition(pList); i = getNextPosition(i))
        {
            printf("%5d", getElement(i));
        }
    }
    printf("\n");
}

void printCreateResult(seqList *pList)
{
    printf("The sequence list has been created and initiated by %d random numerbers", SIZE);
    printList(pList);
}

void printListLength(seqList *pList)
{
    printf("\tThe length of the sequence is %d\n", getLength(pList));
}

void exchangeEasy(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void exchangeListData(listData *oldFirstPosition, listData *newFirstPosition, listData *oldLastPosition, listData *newLastPosition)
{
    if ((newFirstPosition == oldLastPosition) && (newLastPosition == oldFirstPosition))
    {
        exchangeEasy(oldLastPosition, oldFirstPosition);
    }
    else if (newFirstPosition == oldLastPosition)
    {
        exchangeEasy(oldLastPosition, newLastPosition);
        newFirstPosition = newLastPosition;
        exchangeEasy(oldFirstPosition, newFirstPosition);
    }
    else if (newLastPosition == oldFirstPosition)
    {
        exchangeEasy(oldFirstPosition, newFirstPosition);
        newLastPosition = newFirstPosition;
        exchangeEasy(oldLastPosition, newLastPosition);
    }
    else
    {
        exchangeEasy(oldFirstPosition, newFirstPosition);
        exchangeEasy(oldLastPosition, newLastPosition);
    }
}

void sortList(seqList *pList, int sortOrder)
{
    for (position firstPos = getBeginPosition(pList), lastPos = getEndPosition(pList) - 1;
         firstPos <= lastPos;
         firstPos++, lastPos--)
    {
        listData *maxDataPos = firstPos;
        listData *minDataPos = firstPos;
        for (position i = getNextPosition(firstPos); i <= lastPos; i = getNextPosition(i))
        {
            if (*i > *maxDataPos)
            {
                maxDataPos = i;
            }
            else if (*i < *minDataPos)
            {
                minDataPos = i;
            }
        }
        if (sortOrder == 1)
        {
            exchangeListData(firstPos, minDataPos, lastPos, maxDataPos);
        }
        else if (sortOrder == 0)
        {
            exchangeListData(firstPos, maxDataPos, lastPos, minDataPos);
        }
    }
}

int getAndPrintSortOrder(void) // value 1 returned indicates the sort in ascending order.
{
    char ch;
    printf("Press ENTER to sort in ascending order. Others for descending order:");
    fflush(stdin);
    scanf("%c", &ch);
    if (ch == '\n')
    {
        printf("The sorted list in ascending order is:");
        return 1;
    }
    else
    {
        printf("The sorted list in descending order is:");
        return 0;
    }
}

void searchBySerialNumber(seqList *pList)
{
    printf("Please input a location to search:");
    int serialNumber;
    scanf("%d", &serialNumber);
    printf("The value of %d in the sequence list is: %d",
           serialNumber, getElement(getPosition(pList, serialNumber)));
}

int getSerialNumber(seqList *pList, position pos)
{
    return pos - getBeginPosition(pList) + 1;
}

void searchByValue(seqList *pList)
{
    printf("Please input a number to search:");
    listData value;
    scanf("%d", &value);
    printf("The location of %d in the sequence list is: %d",
           value, getSerialNumber(pList, locateElement(pList, value)));
}

void insertBySerialNumber(seqList *pList)
{
    printf("Please input the location to be inserted:");
    int serialNumber;
    scanf("%d", &serialNumber);
    printf("Please input a number to be inserted:");
    listData value;
    scanf("%d", &value);
    if (isCorrect(insertBefore(pList,
                               getPosition(pList, serialNumber),
                               value)))
    {
        printf("Insertion Success");
        printList(pList);
    }
}

void deleteBySerialNumber(seqList *pList)
{
    printf("Please input a location to delete:");
    int serialNumber;
    scanf("%d", &serialNumber);
    resultOfOperateList deleteResult = deleteElement(pList,
                                                     getPosition(pList, serialNumber));
    if (isCorrect(deleteResult.parametersForJudging))
    {
        printf("The location of %d in the sequence list has been deleted: %d",
               serialNumber, deleteResult.dataOperated);
    }
}

void deleteByValue(seqList *pList)
{
    printf("Please input a number to be deleted:");
    listData value;
    scanf("%d", &value);
    int count = 0;
    while (isCorrect(deleteElement(pList, locateElement(pList, value)).parametersForJudging))
    {
        count++;
    }
    printf("There are %d of %d deleted in the sequence list.", count, value);
}

void deleteDuplicate(seqList *pList)
{
    for (position i = getBeginPosition(pList); i != getEndPosition(pList); i = getNextPosition(i))
    {
        position j = getNextPosition(i);
        while (j != getEndPosition(pList))
        {
            if (*j == *i)
            {
                deleteElement(pList, j);
            }
            else
            {
                j = getNextPosition(j);
            }
        }
    }
    printf("All the duplicate elements have been deleted.");
    printList(pList);
}

void reverseList(seqList *pList)
{
    for (position i = getBeginPosition(pList), j = getEndPosition(pList) - 1;
         i <= j;
         i = getNextPosition(i), j--)
    {
        exchangeEasy(i, j);
    }
}

void partitionList(seqList *pList, int partitionValue)
{
    seqList smaller = createList(pList->listLength);
    seqList equal = createList(pList->listLength);
    seqList larger = createList(pList->listLength);
    for (position i = getBeginPosition(pList); i != getEndPosition(pList); i = getNextPosition(i))
    {
        if (*i < partitionValue)
        {
            insertBefore(&smaller, getEndPosition(&smaller), *i);
        }
        else if (*i == partitionValue)
        {
            insertBefore(&equal, getEndPosition(&equal), *i);
        }
        else
        {
            insertBefore(&larger, getEndPosition(&larger), *i);
        }
    }
    clearList(pList);
    for (position i = getBeginPosition(&smaller); i != getEndPosition(&smaller); i = getNextPosition(i))
    {
        insertBefore(pList, getEndPosition(pList), *i);
    }
    for (position i = getBeginPosition(&equal); i != getEndPosition(&equal); i = getNextPosition(i))
    {
        insertBefore(pList, getEndPosition(pList), *i);
    }
    for (position i = getBeginPosition(&larger); i != getEndPosition(&larger); i = getNextPosition(i))
    {
        insertBefore(pList, getEndPosition(pList), *i);
    }
}

void importFromFile(seqList *pList)
{
    *pList = createList(1);
    FILE *fp;
    fp = fopen("./listData.txt", "r"); // First make sure that the path is correct
    if (fp == NULL)
    {
        printf("File %s open wrong!", "listData.txt");
        exit(EXIT_FAILURE);
    }
    listData value;
    while (fscanf(fp, "%d", &value) != EOF)
    {
        insertBefore(pList, getEndPosition(pList), value);
    }
    if (fclose(fp) != 0)
    {
        printf("File %s close wrong!", "listData.txt");
        exit(EXIT_FAILURE);
    }
    printf("Data imported from the \"listData.txt\" success.");
}

void exportToFile(seqList *pList)
{
    FILE *fp;
    if ((fp = fopen("./listDataCopy.txt", "wb")) == NULL) // First make sure that the path is correct
    {
        printf("File %s open wrong!", fp);
    }
    for (position i = getBeginPosition(pList); i != getEndPosition(pList); i = getNextPosition(i))
    {
        fprintf(fp, "%5d", *i);
    }
    if ((fclose(fp)) != 0)
    {
        printf("File %s close wrong!", fp);
    }
    printf("Data ouput to the file success.");
}

int getMaxPlatform(seqList *pList)
{
    int maxCount = 1;
    int count = 1;
    for (position i = getBeginPosition(pList); i != getEndPosition(pList) - 1; i = getNextPosition(i))
    {
        if (*i == *getNextPosition(i))
        {
            count++;
        }
        else
        {
            count = 1;
        }
        if (count > maxCount)
        {
            maxCount = count;
        }
    }
    return maxCount;
}
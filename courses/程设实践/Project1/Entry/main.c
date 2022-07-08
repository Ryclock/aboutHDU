/*
 * Copyright(C)
 * All rights reserved.
 * Author : Ryclock HDU
 * Date : 2022-02-21-08.54.14
 * Description : Sequence List Basic System for Sequence List class.
 */

#include <stdio.h>
#include <stdlib.h>
#include "Menu.h"
#include "../Attached/Sequence List/SeqList.h"
#include "Others.h"

char lang = 'C';
seqList list;

void case11(void)
{
    printf("The sequence before inversion is:");
    printList(&list);
    reverseList(&list);
    printf("The sequence after inversion is:");
    printList(&list);
}

void case12(void)
{
    printf("Please input the partition value:");
    int value;
    scanf("%d", &value);
    printf("The sequence before partition:");
    printList(&list);
    partitionList(&list, value);
    printf("The sequence after partition by %d:", value);
    printList(&list);
}

void analysis_Choices(int choice)
{
    switch (choice)
    {
    case 0:
        switchlanguage(&lang);
        Menu(lang);
        break;
    case 1:
        create(&list);
        printCreateResult(&list);
        break;
    case 2:
        printList(&list);
        printListLength(&list);
        break;
    case 3:
        clearList(&list);
        printf("The current sequence list has been clear.");
        break;
    case 4:
        sortList(&list, getAndPrintSortOrder());
        printList(&list);
        break;
    case 5:
        searchBySerialNumber(&list);
        break;
    case 6:
        searchByValue(&list);
        break;
    case 7:
        insertBySerialNumber(&list);
        break;
    case 8:
        deleteBySerialNumber(&list);
        break;
    case 9:
        deleteByValue(&list);
        break;
    case 10:
        deleteDuplicate(&list);
        break;
    case 11:
        case11();
        break;
    case 12:
        case12();
        break;
    case 13:
        importFromFile(&list);
        printList(&list);
        break;
    case 14:
        exportToFile(&list);
        break;
    case 15:
        printf("The max platform is: %d", getMaxPlatform(&list));
        break;
    case 16:
        exit(EXIT_SUCCESS);
        break;
    default:
        printf("\nWrong! Please choose another true number!\n\n");
    }
}

int main(void)
{
    while (1)
    {
        Menu(lang);
        analysis_Choices(inputChoice());
        system("pause");
    }
    return 0;
}

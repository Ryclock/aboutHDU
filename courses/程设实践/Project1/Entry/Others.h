#ifndef _OTHERS_H_INCLUDED_
#define _OTHERS_H_INCLUDED_

int isCorrect(int procedure);

int inputChoice(void);

void switchlanguage(char *pLanguage);

void create(seqList *pList);

void printList(seqList *pList);

void printCreateResult(seqList *pList);

void printListLength(seqList *pList);

void exchangeEasy(int *a, int *b);

void exchangeListData(listData *oldFirstPosition, listData *newFirstPosition, listData *oldLastPosition, listData *newLastPosition);

void sortList(seqList *pList, int sortOrder);

int getAndPrintSortOrder(void); // value 1 returned indicates the sort in ascending order.

void searchBySerialNumber(seqList *pList);

int getSerialNumber(seqList *pList, position pos);

void searchByValue(seqList *pList);

void insertBySerialNumber(seqList *pList);

void deleteBySerialNumber(seqList *pList);

void deleteByValue(seqList *pList);

void deleteDuplicate(seqList *pList);

void reverseList(seqList *pList);

void partitionList(seqList *pList, int partitionValue);

void importFromFile(seqList *pList);

void exportToFile(seqList *pList);

int getMaxPlatform(seqList *pList);

#endif

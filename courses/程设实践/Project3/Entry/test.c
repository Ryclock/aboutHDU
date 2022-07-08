/* test.c -- 测试函数的接口实现 */
#include <stdio.h>
#include <stdlib.h>
#include "test.h"

/* 局部函数原型 */

static bool isExist(Elem_T e, int numOfValue[], const Problem *origin);

static void copyProblem(Problem *des, const Problem *src);

static void result(Problem *origin, Problem *test);

static void shuffleArray(Problem *test);

/* 接口函数 */

void Init(Problem *p)
{
    srand((unsigned)time(0));
    for (int i = 0; i < p->size; i++)
    {
        p->arr[i].key = rand() % p->range + 1;
    }
}

bool isTrue(const Problem *origin, const Problem *sorted)
{
    int *numOfValue = (int *)calloc(origin->range + 1, sizeof(int));
    for (int i = 0; i < origin->size; i++)
    {
        numOfValue[origin->arr[i].key]++;
    }
    for (int i = 0; i < sorted->size - 1; i++)
    {
        if (!isExist(sorted->arr[i], numOfValue, origin))
        {
            printf("\nPosition %d isn't exited", i + 1);
            free(numOfValue);
            return false;
        }
        if (sorted->arr[i].key > sorted->arr[i + 1].key)
        {
            printf("\nPosition %d is bigger than the one after", i + 1);
            free(numOfValue);
            return false;
        }
    }
    free(numOfValue);
    return true;
}

void print(const Problem *p)
{
    printf("\nArray[%d]: {", p->size);
    for (int i = 0; i < p->size; i++)
    {
        if (i == p->size - 1)
        {
            printf(" %d};", p->arr[i].key);
        }
        else
        {
            printf(" %d,", p->arr[i].key);
        }
    }
}

void TestOneSort(Problem *origin, void (*pfunction)(Problem *p))
{
    printf("\nFirst, a completely random array:");
    Problem *test = (Problem *)malloc(sizeof(Problem) + sizeof(Elem_T) * origin->size);
    copyProblem(test, origin);
    pfunction(test);
    result(origin, test);
    printf("\nThen, an almost ordered arrays:");
    Problem *fake = (Problem *)malloc(sizeof(Problem) + sizeof(Elem_T) * test->size);
    shuffleArray(test);
    copyProblem(fake, test);
    pfunction(test);
    result(fake, test);
    printf("\nThe end of this sorting method.");
    free(test);
    test = NULL;
    system("pause");
}

void TestMixedSort(Problem *origin, void (*pfunction1)(Problem *p1), void (*pfunction2)(Problem *p2))
{
    printf("\nFirst, a completely random array:");
    Problem *test = (Problem *)malloc(sizeof(Problem) + sizeof(Elem_T) * origin->size);
    copyProblem(test, origin);
    pfunction1(test);
    result(origin, test);
    printf("\nThen, an almost ordered arrays:");
    Problem *fake = (Problem *)malloc(sizeof(Problem) + sizeof(Elem_T) * test->size);
    shuffleArray(test);
    copyProblem(fake, test);
    pfunction2(test);
    result(fake, test);
    printf("\nThe end of this sorting method.");
    free(test);
    test = NULL;
    system("pause");
}

void BubbleSortTest(Problem *p)
{
    start = clock();
    BubbleSort(p->arr, p->size);
    finish = clock();
    printf("\n\tBubbleSort cost: %lf seconds", (double)(finish - start) / CLOCKS_PER_SEC);
}

void SelectSortTest(Problem *p)
{
    start = clock();
    SelectSort(p->arr, p->size);
    finish = clock();
    printf("\n\tSelectSort cost: %lf seconds", (double)(finish - start) / CLOCKS_PER_SEC);
}

void InsertionSortTest(Problem *p)
{
    start = clock();
    InsertionSort(p->arr, p->size);
    finish = clock();
    printf("\n\tInsertionSort cost: %lf seconds", (double)(finish - start) / CLOCKS_PER_SEC);
}

void MergeSortTest(Problem *p)
{
    Elem_T *temp = NULL;
    temp = (Elem_T *)malloc(p->size * sizeof(Elem_T));
    start = clock();
    MergeSort(p->arr, 0, p->size - 1, temp);
    finish = clock();
    printf("\n\tMergeSort cost: %lf seconds", (double)(finish - start) / CLOCKS_PER_SEC);
    free(temp);
    temp = NULL;
}

void QuickSortTest(Problem *p)
{
    start = clock();
    QuickSort(p->arr, 0, p->size - 1);
    finish = clock();
    printf("\n\tQuickSort cost: %lf seconds", (double)(finish - start) / CLOCKS_PER_SEC);
}

void CountSortTest(Problem *p)
{
    Elem_T *temp;
    temp = (Elem_T *)malloc(p->size * sizeof(Elem_T));
    for (int i = 0; i < p->size; i++)
    {
        temp[i].key = p->arr[i].key;
    }
    start = clock();
    CountSort(p->arr, temp, p->size, p->range);
    finish = clock();
    printf("\n\tCountSort cost: %lf seconds", (double)(finish - start) / CLOCKS_PER_SEC);
    free(temp);
    temp = NULL;
}

void BucketSortTest(Problem *p)
{
    start = clock();
    BucketSort(p->arr, p->size, NBUCKET);
    finish = clock();
    printf("\n\tBucketSort cost: %lf seconds", (double)(finish - start) / CLOCKS_PER_SEC);
}

void RadixSortTest(Problem *p)
{
    int maxDigit = 0, base = 10;
    int temp = p->range;
    while (temp != 0)
    {
        maxDigit++;
        temp /= base;
    }
    start = clock();
    RadixSort(p->arr, p->size, base, maxDigit);
    finish = clock();
    printf("\n\tRadixSort cost: %lf seconds", (double)(finish - start) / CLOCKS_PER_SEC);
}

/* 局部函数 */

static bool isExist(Elem_T e, int numOfValue[], const Problem *origin)
{
    if (e.key > origin->range)
    {
        return false;
    }
    for (int i = 0; i < origin->size; i++)
    {
        if (origin->arr[i].key == e.key && numOfValue[e.key] > 0)
        {
            numOfValue[e.key]--;
            return true;
        }
    }
}

static void copyProblem(Problem *des, const Problem *src)
{
    des->size = src->size;
    des->range = src->range;
    for (int i = 0; i < des->size; i++)
    {
        des->arr[i].key = src->arr[i].key;
    }
}
static void result(Problem *origin, Problem *test)
{
    if (isTrue(origin, test))
    {
        printf("\n\tSort result is true.");
    }
    else
    {
        printf("\n\tError: sort result is wrong!!");
    }
}

static void shuffleArray(Problem *test)
{
    srand((unsigned)time(0));
    int n = 0;
    while (n == 0)
    {
        n = rand() % 10;
    }
    for (int i = 0; i < n; i++)
    {
        int j = rand() % test->size;
        int newValue = rand() % test->range + 1;
        test->arr[j].key = newValue;
    }
}
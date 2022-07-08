/* test.h -- 测试函数的接口 */
#ifndef TEST_H
#define TEST_H

#include <stdbool.h>
#include <time.h>
#include "sort.h"

#define NBUCKET 100

/* 一般类型定义 */

typedef struct Array
{
    int size;
    int range;
    Elem_T arr[0];
} Problem;

/* 全局变量 */

extern clock_t start;

/* 函数原型 */

/*void TestAllSort(Problem *p); */

void Init(Problem *p);

bool isTrue(const Problem *origin, const Problem *sorted);

void print(const Problem *p);

void TestOneSort(Problem *origin, void (*pfunction)(Problem *p));

void TestMixedSort(Problem *origin, void (*pfunction1)(Problem *p1), void (*pfunction2)(Problem *p2));

void BubbleSortTest(Problem *p);

void SelectSortTest(Problem *p);

void InsertionSortTest(Problem *p);

void MergeSortTest(Problem *p);

void QuickSortTest(Problem *p);

void CountSortTest(Problem *p);

void BucketSortTest(Problem *p);

void RadixSortTest(Problem *p);

#endif

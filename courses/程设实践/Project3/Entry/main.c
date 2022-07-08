/*
 * Copyright(C)
 * All rights reserved.
 * Author : JIANG YAONAN 2102115 HDU
 * Date : 2022-03-30
 * Description : All kinds of sorting methods.
 */

#include <stdlib.h>
#include "test.h"

#define LEN 1000000
#define RANGE 1000000

int main(void)
{
    Problem *origin = (Problem *)malloc(sizeof(Problem) + sizeof(Elem_T) * LEN);
    origin->size = LEN;
    origin->range = RANGE;
    Init(origin);

    // TestOneSort(origin, BubbleSortTest);
    // TestMixedSort(origin, QuickSortTest, BubbleSortTest);
    // TestOneSort(origin, SelectSortTest);
    // TestMixedSort(origin, QuickSortTest, SelectSortTest);
    // TestOneSort(origin, InsertionSortTest);
    // TestMixedSort(origin, QuickSortTest, InsertionSortTest);
    // TestOneSort(origin, MergeSortTest);
    // TestOneSort(origin, QuickSortTest);
    // TestOneSort(origin, CountSortTest);
    // TestMixedSort(origin, QuickSortTest, CountSortTest);
    // TestOneSort(origin, BucketSortTest);
    // TestOneSort(origin, RadixSortTest);
    return 0;
}

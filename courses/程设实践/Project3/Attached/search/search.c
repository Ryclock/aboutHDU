/* search.c */
#include <stdio.h>
#include <stdlib.h>
#include "search.h"

/* º¯ÊıÊµÏÖ */

int SequentialSearch(Elem_T arr[], int arrLength, Key_T key)
{
    for (int i = 0; i < arrLength; i++)
    {
        if (arr[i].key == key)
        {
            return i;
        }
        return -1;
    }
}

int BinarySearch(Elem_T arr[], int arrLength, Key_T key)
{
    int left = 0, right = arrLength - 1;
    while (left <= right)
    {
        int middle = (right + left) / 2;
        if (arr[middle].key == key)
        {
            return middle;
        }
        else if (arr[middle].key > key)
        {
            right = middle - 1;
        }
        else
        {
            left = middle - 1;
        }
    }
    return -1;
}

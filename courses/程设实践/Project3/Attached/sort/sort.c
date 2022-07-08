/* sort.c -- �������Ľӿ�ʵ�� */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sort.h"

/* �ֲ�����ԭ�� */

static bool needToAdjust(Key_T smaller, Key_T bigger);

static void swap(Elem_T e1, Elem_T e2);

static void merge(Elem_T arr[], int left, int middle, int right, Elem_T temp[]);

static void copyArr(Elem_T des[], Elem_T src[], int start, int end);

static int QuickPass(Elem_T arr[], int left, int right);

static void initialICount(int iCount[], int maxKey);

static void getICount(Elem_T src[], int n, int iCount[]);

/* �ӿں��� */

void BubbleSort(Elem_T arr[], int arrLength)
{
    for (int i = 0; i < arrLength; i++)
    {
        for (int j = 0; j < arrLength; j++)
        {
            if (needToAdjust(arr[j].key, arr[j + 1].key))
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void SelectSort(Elem_T arr[], int arrLength)
{
    for (int i = 0; i < arrLength; i++)
    {
        int min = i;
        for (int j = i + 1; j < arrLength; j++)
        {
            if (needToAdjust(arr[min].key, arr[j].key))
            {
                min = j;
            }
        }
        swap(arr[i], arr[min]);
    }
}

void InsertionSort(Elem_T arr[], int arrLength)
{
    for (int i = 0; i < arrLength; i++)
    {
        Elem_T temp = arr[i];
        int j = i - 1;
        while (j >= 0 && temp.key < arr[j].key)
        {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = temp;
    }
}

void MergeSort(Elem_T arr[], int left, int right, Elem_T temp[])
{
    if (left >= right)
    {
        return;
    }
    int middle = (left + right) / 2;
    MergeSort(arr, left, middle, temp);
    MergeSort(arr, middle + 1, right, temp);
    merge(arr, left, middle, right, temp);
    copyArr(arr, temp, left, right);
}
void QuickSort(Elem_T arr[], int left, int right)
{
    if (left >= right)
    {
        return;
    }
    int pivot = QuickPass(arr, left, right);
    QuickSort(arr, left, pivot - 1);
    QuickSort(arr, pivot + 1, right);
}

void CountSort(Elem_T des[], Elem_T src[], int n, int maxKey, int iCount[])
{
    initialICount(iCount, maxKey);
    getICount(src, n, iCount);
    for (int i = 0, start = 0; i < maxKey + 1; i++)
    {
        int next = start + iCount[i];
        iCount[i] = start;
        start = next;
    }
    for (int i = 0; i < n; i++)
    {
        des[iCount[src[i].key]++] = src[i];
    }
}

void BucketSort(Elem_T arr[], int n, int bucketN)
{
    /* ����bucketN����Ͱ��ԭ��ģ�ͣ������1-bucketN */

    for (int i = 0; i < n; i++)
    {
        /* ����arr[i].key�����Ͱ��k */
        /* ��arr[i]����k��Ͱ�� */
    }
    for (int i = 0; i < bucketN; i++)
    {
        /* ��i��Ͱ��Ԫ������ */
        /* ��i��Ͱ��Ԫ�����η�������arr����ĩβ��������Ԫ�غ��� */
    }
}

void RadixSort(Elem_T arr[], int n, int base, int maxDigit)
{
    for (int i = 0; i < maxDigit; i++)
    {
        /* ����base����Ͱ�����1-base */

        for (int j = 0; j < n; j++)
        {
            /* ����arr[i].key�ĵ�iλ�������Ͱ��k */
            /* ��arr[i]����k��Ͱ�� */
        }
        for (int k = 0; k < base; k++)
        {
            /* ˳���ռ�k��Ͱ������Ԫ�أ��޸�ԭ����arr */
        }
    }
}

/* �ֲ����� */

static bool needToAdjust(Key_T smaller, Key_T bigger)
{
    return (smaller > bigger);
}

static void swap(Elem_T e1, Elem_T e2)
{
    Elem_T temp;
    temp = e1;
    e1 = e2;
    e2 = temp;
}

static void merge(Elem_T arr[], int left, int middle, int right, Elem_T temp[])
{
    int k = left;
    int i = left;
    int j = middle + 1;
    while (i <= middle && j <= right)
    {
        if (arr[i].key <= arr[j].key)
        {
            temp[k++] = arr[i++];
        }
        else
        {
            temp[k++] = arr[j++];
        }
    }
    while (i <= middle)
    {
        temp[k++] = arr[i++];
    }
    while (j <= right)
    {
        temp[k++] = arr[j++];
    }
}

static void copyArr(Elem_T des[], Elem_T src[], int start, int end)
{
    for (int i = start; i < end; i++)
    {
        des[i] = src[i];
    }
}

static int QuickPass(Elem_T arr[], int left, int right)
{
    Elem_T temp = arr[left];
    while (left < right)
    {
        while (left < right && arr[right].key >= temp.key)
        {
            right--;
        }
        if (left == right)
        {
            break;
        }
        arr[left++] = arr[right];
        while (left < right && arr[left].key <= temp.key)
        {
            left++;
        }
        if (left == right)
        {
            break;
        }
        arr[right--] = arr[left];
    }
    arr[left] = temp;
    return left;
}

static void initialICount(int iCount[], int maxKey)
{
    for (int key = 0; key < maxKey + 1; key++)
    {
        iCount[key] = 0;
    }
}
static void getICount(Elem_T src[], int n, int iCount[])
{
    for (int i = 0; i < n; i++)
    {
        iCount[src[i].key]++;
    }
}

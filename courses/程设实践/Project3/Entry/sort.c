/* sort.c -- �������Ľӿ�ʵ�� */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sort.h"

/* ��̬ȫ�ֱ������� */

static bool flag = true;

/* �ֲ�����ԭ�� */

static bool needToAdjust(Key_T smaller, Key_T bigger);

static void swap(Elem_T *e1, Elem_T *e2);

static void merge(Elem_T arr[], int left, int middle, int right, Elem_T temp[]);

static void copyArr(Elem_T des[], Elem_T src[], int start, int end);

static int QuickPass(Elem_T arr[], int left, int right);

static void initialICount(int iCount[], int maxKey);

static void getICount(const Elem_T src[], int n, int iCount[]);

static bool timeOut(void);

/* �ӿں��� */

void BubbleSort(Elem_T arr[], int arrLength)
{
    for (int i = 0; i < arrLength - 1; i++)
    {
        if (timeOut())
        {
            printf("Error: Over time limited!!");
            system("pause");
            exit(1);
        }
        for (int j = 0; j < arrLength - 1 - i; j++)
        {
            if (needToAdjust(arr[j].key, arr[j + 1].key))
            {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

void SelectSort(Elem_T arr[], int arrLength)
{
    for (int i = 0; i < arrLength; i++)
    {
        if (timeOut())
        {
            printf("Error: Over time limited!!");
            system("pause");
            exit(1);
        }
        int min = i;
        for (int j = i + 1; j < arrLength; j++)
        {
            if (needToAdjust(arr[min].key, arr[j].key))
            {
                min = j;
            }
        }
        swap(&arr[i], &arr[min]);
    }
}

void InsertionSort(Elem_T arr[], int arrLength)
{
    for (int i = 0; i < arrLength; i++)
    {
        if (timeOut())
        {
            printf("Error: Over time limited!!");
            system("pause");
            exit(1);
        }
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
    if (flag == false)
    {
        return;
    }
    if (timeOut())
    {
        printf("Error: Over time limited!!");
        flag = false;
        system("pause");
        exit(1);
    }
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
    if (flag == false)
    {
        return;
    }
    if (timeOut())
    {
        printf("Error: Over time limited!!");
        flag = false;
        system("pause");
        exit(1);
    }
    if (left >= right)
    {
        return;
    }
    int pivot = QuickPass(arr, left, right);
    QuickSort(arr, left, pivot - 1);
    QuickSort(arr, pivot + 1, right);
}

void CountSort(Elem_T des[], const Elem_T src[], int arrLength, int maxKey)
{
    int iCount[maxKey + 1];
    initialICount(iCount, maxKey);
    getICount(src, arrLength, iCount);
    for (int i = 0, start = 0; i < maxKey + 1; i++)
    {
        if (timeOut())
        {
            printf("Error: Over time limited!!");
            system("pause");
            exit(1);
        }
        int next = start + iCount[i];
        iCount[i] = start;
        start = next;
    }
    for (int i = 0; i < arrLength; i++)
    {
        if (timeOut())
        {
            printf("Error: Over time limited!!");
            system("pause");
            exit(1);
        }
        des[iCount[src[i].key]++] = src[i];
    }
}

void BucketSort(Elem_T arr[], int arrLength, int bucketN)
{
    /* ����bucketN����Ͱ�����0 - bucketN-1 */
    struct node
    {
        Elem_T data;
        struct node *next;
    };
    struct node **bucket = (struct node **)malloc(sizeof(struct node *) * bucketN);
    for (int i = 0; i < bucketN; i++)
    {
        bucket[i] = NULL;
    }
    /* ����Ͱ��,��Ͱ */
    for (int i = 0; i < arrLength; i++)
    {
        if (timeOut())
        {
            printf("Error: Over time limited!!");
            system("pause");
            exit(1);
        }
        /* ����arr[i].key�����Ͱ��k */
        int k = (arr[i].key - 1) / (arrLength / bucketN);
        /* ����arr[i]����k��Ͱ */
        struct node *current = (struct node *)malloc(sizeof(struct node));
        current->data = arr[i],
        current->next = bucket[k],
        bucket[k] = current;
    }
    /* ���� */
    for (int i = 0, now = 0; i < bucketN; i++)
    {
        if (timeOut())
        {
            printf("Error: Over time limited!!");
            system("pause");
            exit(1);
        }
        /* ��i��Ͱ��Ԫ������ */
        int last = now;
        while (bucket[i] != NULL)
        {
            arr[now++] = bucket[i]->data;
            bucket[i] = bucket[i]->next;
        }
        Elem_T *temp = NULL;
        temp = (Elem_T *)malloc((now - last) * sizeof(Elem_T));
        MergeSort(arr, last, now - 1, temp);
        free(temp);
        temp = NULL;
    }
    free(bucket);
    bucket = NULL;
}

void RadixSort(Elem_T arr[], int arrLength, int base, int maxDigit)
{
    for (int i = 1; i <= maxDigit; i++)
    {
        /* ����base����Ͱ�����0 - base-1 */
        struct node
        {
            Elem_T data;
            struct node *next;
        };
        struct node **bucket = (struct node **)malloc(sizeof(struct node *) * base);
        for (int i = 0; i < base; i++)
        {
            bucket[i] = NULL;
        }
        for (int j = arrLength - 1; j >= 0; j--)
        {
            if (timeOut())
            {
                printf("Error: Over time limited!!");
                system("pause");
                exit(1);
            }
            /* ����arr[j].key�ĵ�iλ�������Ͱ��k */
            int k = (arr[j].key / (int)pow(base, i - 1)) % base;
            /* ��arr[j]����k��Ͱ�� */
            struct node *current = (struct node *)malloc(sizeof(struct node));
            current->data = arr[j],
            current->next = bucket[k],
            bucket[k] = current;
        }
        for (int i = 0, k = 0; i < base; i++)
        {
            if (timeOut())
            {
                printf("Error: Over time limited!!");
                system("pause");
                exit(1);
            }
            /* ˳���ռ�k��Ͱ������Ԫ�أ��޸�ԭ����arr*/
            while (bucket[i] != NULL)
            {
                arr[k++] = bucket[i]->data;
                bucket[i] = bucket[i]->next;
            }
        }
        free(bucket);
        bucket = NULL;
    }
}

/* �ֲ����� */

static bool needToAdjust(Key_T smaller, Key_T bigger)
{
    return (smaller > bigger);
}

static void swap(Elem_T *e1, Elem_T *e2)
{
    Elem_T temp;
    temp = *e1;
    *e1 = *e2;
    *e2 = temp;
}

static void merge(Elem_T arr[], int left, int middle, int right, Elem_T temp[])
{
    int k = 0;
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
    if (i == middle + 1)
    {
        while (j <= right)
        {
            temp[k++] = arr[j++];
        }
    }
    if (j == right + 1)
    {
        while (i <= middle)
        {
            temp[k++] = arr[i++];
        }
    }
}

static void copyArr(Elem_T des[], Elem_T src[], int start, int end)
{
    for (int i = start, j = 0; j <= end - start; i++, j++)
    {
        des[i] = src[j];
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
static void getICount(const Elem_T src[], int arrLength, int iCount[])
{
    for (int i = 0; i < arrLength; i++)
    {
        iCount[src[i].key]++;
    }
}

static bool timeOut(void)
{
    finish = clock();
    return (int)(finish - start) / CLOCKS_PER_SEC > LIMITSECONDS;
}
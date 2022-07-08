/* sort.h -- 排序函数的接口 */
#ifndef SORT_H
#define SORT_H

/* 一般类型定义 */

typedef int Key_T;

typedef struct
{
    Key_T key;
} Elem_T;

/* 函数原型 */

/*
    操作：冒泡排序
    后置条件：数组arr将被按照升序排列；
 */
void BubbleSort(Elem_T arr[], int arrLength);

/*
    操作：选择排序
    后置条件：数组arr将被按照升序排列；
 */
void SelectSort(Elem_T arr[], int arrLength);

/*
    操作：插入排序
    后置条件：数组arr将被按照升序排列；
 */
void InsertionSort(Elem_T arr[], int arrLength);

/*
    操作：归并排序
    后置条件：数组arr将被按照升序排列；
 */
void MergeSort(Elem_T arr[], int left, int right, Elem_T temp[]);

/*
    操作：快速排序
    前置条件：left为数组的下标；
             right为数组的下标；
    后置条件：数组arr将被按照升序排列；
 */
void QuickSort(Elem_T arr[], int left, int right);

/*
    操作：计数排序
    前置条件：0 - maxKey范围不大；
             且Key_T为int的别名；
    后置条件：数组arr将被按照升序排列；
 */
void CountSort(Elem_T des[], Elem_T src[], int n, int maxKey, int iCount[]);

/*
    操作：桶排序
    前置条件：key均匀分布，且可缩放至(0,1)范围；
    后置条件：数组arr将被按照升序排列；
 */
void BucketSort(Elem_T arr[], int n, int bucketN);

/*
    操作：基数排序
    前置条件：每一位进行排序时有使用桶的知识；
    后置条件：数组arr将被按照升序排列；
 */
void RadixSort(Elem_T arr[], int n, int base, int maxDigit);

#endif

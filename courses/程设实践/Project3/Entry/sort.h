/* sort.h -- �������Ľӿ� */
#ifndef SORT_H
#define SORT_H

#include <stdbool.h>
#include <time.h>
#define LIMITSECONDS 300
#define LIMITBUFFER 2048

/* һ�����Ͷ��� */

typedef int Key_T;

typedef struct
{
    Key_T key;
} Elem_T;

/* ȫ�ֱ��� */

clock_t start, finish;

/* ����ԭ�� */

/*
    ������ð������
    ��������������arr���������������У�
 */
void BubbleSort(Elem_T arr[], int arrLength);

/*
    ������ѡ������
    ��������������arr���������������У�
 */
void SelectSort(Elem_T arr[], int arrLength);

/*
    ��������������
    ��������������arr���������������У�
 */
void InsertionSort(Elem_T arr[], int arrLength);

/*
    �������鲢����
    ǰ��������leftΪ��Ҫ���򲿷ֵ�����ˣ�
             rightΪ��Ҫ���򲿷ֵ����Ҷˣ�
    ��������������arr���������������У�
 */
void MergeSort(Elem_T arr[], int left, int right, Elem_T temp[]);

/*
    ��������������
    ǰ��������leftΪ������±ꣻ
             rightΪ������±ꣻ
    ��������������arr���������������У�
 */
void QuickSort(Elem_T arr[], int left, int right);

/*
    ��������������
    ǰ��������maxKeyΪ����Ԫ�����ޣ�
             0 - maxKey��Χ����
             ��Key_TΪint�ı�����
    ��������������des��������src���������н����
 */
void CountSort(Elem_T des[], const Elem_T src[], int arrLength, int maxKey);

/*
    ������Ͱ����
    ǰ��������key���ȷֲ����ҿ�������(0,1)��Χ��
             bucketN����Ͱ�ĸ������㵽bucketN-1��
    ��������������arr���������������У�
 */
void BucketSort(Elem_T arr[], int arrLength, int bucketN);

/*
    ��������������
    ǰ������������key��ÿһλ�ֱ����Ͱ����
    ��������������arr���������������У�
 */
void RadixSort(Elem_T arr[], int arrLength, int base, int maxDigit);

#endif

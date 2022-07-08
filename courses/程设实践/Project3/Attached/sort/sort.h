/* sort.h -- �������Ľӿ� */
#ifndef SORT_H
#define SORT_H

/* һ�����Ͷ��� */

typedef int Key_T;

typedef struct
{
    Key_T key;
} Elem_T;

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
    ǰ��������0 - maxKey��Χ����
             ��Key_TΪint�ı�����
    ��������������arr���������������У�
 */
void CountSort(Elem_T des[], Elem_T src[], int n, int maxKey, int iCount[]);

/*
    ������Ͱ����
    ǰ��������key���ȷֲ����ҿ�������(0,1)��Χ��
    ��������������arr���������������У�
 */
void BucketSort(Elem_T arr[], int n, int bucketN);

/*
    ��������������
    ǰ��������ÿһλ��������ʱ��ʹ��Ͱ��֪ʶ��
    ��������������arr���������������У�
 */
void RadixSort(Elem_T arr[], int n, int base, int maxDigit);

#endif

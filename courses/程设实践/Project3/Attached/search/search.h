/* search.h -- ���Һ����Ľӿ� */
#ifndef SEARCH_H
#define SEARCH_H

/* һ�����Ͷ��� */

typedef int Key_T;

typedef struct
{
    Key_T key;
} Elem_T;

/* ����ԭ�� */

/*
    ������˳�����
    ǰ��������keyΪ��Ҫ���ҵ�����
    ������������key������arr�У���������key����Ӧ���±꣨��0��ʼ����
             ����������-1��
 */
int SequentialSearch(Elem_T arr[], int arrLength, Key_T key);

/*
    ���������ֲ���
    ǰ������������arrΪ�������飬keyΪ��Ҫ���ҵ����ݣ�
    ������������key������arr�У���������key����Ӧ���±꣨��0��ʼ����
             ����������-1��
 */
int BinarySearch(Elem_T arr[], int arrLength, Key_T key);

#endif

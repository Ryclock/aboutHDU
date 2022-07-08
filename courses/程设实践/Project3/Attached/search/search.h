/* search.h -- 查找函数的接口 */
#ifndef SEARCH_H
#define SEARCH_H

/* 一般类型定义 */

typedef int Key_T;

typedef struct
{
    Key_T key;
} Elem_T;

/* 函数原型 */

/*
    操作：顺序查找
    前置条件：key为需要查找的数据
    后置条件：若key在数组arr中，则函数返回key所对应的下标（从0开始）；
             否则函数返回-1；
 */
int SequentialSearch(Elem_T arr[], int arrLength, Key_T key);

/*
    操作：二分查找
    前置条件：数组arr为升序数组，key为需要查找的数据；
    后置条件：若key在数组arr中，则函数返回key所对应的下标（从0开始）：
             否则函数返回-1；
 */
int BinarySearch(Elem_T arr[], int arrLength, Key_T key);

#endif

#include <stdio.h>
#include <stdlib.h>
#include "SeqQueue.h"

void output(SeqQueue *q)
{
    while (!isEmpty(q))
    {
        printf("%d  ", getTopData(q));
        pop(q);
    }
}

void input(SeqQueue *q)
{
    DataType x = 0;
    printf("please input element:");
    do
    {
        scanf("%d", &x);
        push(q, x);
    } while (x != 888);
}

void main(void)
{
    SeqQueue p, *q = &p;
    init(q);
    input(q);
    system("pause");
    output(q);
    system("pause");
    destroy(q);
    system("pause");
}
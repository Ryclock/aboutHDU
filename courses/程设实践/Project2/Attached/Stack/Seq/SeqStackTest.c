#include <stdio.h>
#include <stdlib.h>
#include "SeqStack.h"

void output(SeqStack *s)
{
    while (!isEmpty(s))
    {
        printf("%d  ", getTopData(s));
        pop(s);
    }
}

void input(SeqStack *s)
{
    DataType x = 0;
    printf("please input element:");
    do
    {
        scanf("%d", &x);
        push(s, x);
    } while (x != 888);
}

void main(void)
{
    SeqStack p, *s = &p;
    init(s);
    input(s);
    system("pause");
    output(s);
    system("pause");
    destroy(s);
    system("pause");
}
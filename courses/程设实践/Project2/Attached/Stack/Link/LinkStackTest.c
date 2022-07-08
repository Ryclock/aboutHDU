#include <stdio.h>
#include <stdlib.h>
#include "LinkStack.h"

void output(LinkStack *s)
{
    while (!isEmpty(s))
    {
        printf("%d  ", getTopData(s));
        pop(s);
    }
}

void input(LinkStack *s)
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
    LinkStack p, *s = &p;
    init(s);
    input(s);
    system("pause");
    output(s);
    system("pause");
    destroy(s);
    system("pause");
}
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Queen.h"

void main(void)
{
    SQueen theProblem, *p = &theProblem;
    initProblem(p);
    system("pause");
    try(p, 1);
    system("pause");
}
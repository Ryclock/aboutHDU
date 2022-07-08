#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Backpack.h"

void main(void)
{
    SBag theProblem, *p = &theProblem;
    initProblem(p);
    system("pause");
    try(p, 1);
    printSolution(p);
    system("pause");
}
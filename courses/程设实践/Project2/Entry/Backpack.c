#include <stdio.h>
#include <stdlib.h>
#include "Backpack.h"

void backpackTest(void)
{
    SBag problem, *p = &problem;
    initBagProblem(p);
    printf("\n\n\tPress Any key to show the solution.");
    system("pause");
    tryBagSolution(p, 1);
    printf("\n\tThere are %d solutions", p->countOkSolution);
}

void initBagProblem(SBag *pProblem)
{
    int temp;
    printf("Please input the number of items(2-50): ");
    scanf("%d", &temp);
    if (temp < 2 || temp > 50)
    {
        printf("Error!");
        system("pause");
        exit(1);
    }
    pProblem->n = temp;

    printf("Please input the volumn of bag(5-500): ");
    scanf("%d", &temp);
    if (temp < 5 || temp > 500)
    {
        printf("Error!");
        system("pause");
        exit(1);
    }
    pProblem->volumnLimit = pProblem->volumnLeft = temp;

    for (int i = 0; i < pProblem->n; i++)
    {
        printf("Please input the volumn of item %d: ", i + 1);
        scanf("%d", &temp);
        pProblem->Goods[i].volumn = temp;
    }
    pProblem->countOkSolution = 0;
    qsort(pProblem->Goods, pProblem->n, sizeof(SGood), compareGood);
}

int compareGood(const void *p1, const void *p2)
{
    const SGood *pGood1 = (const SGood *)p1;
    const SGood *pGood2 = (const SGood *)p2;
    if (pGood1->volumn < pGood2->volumn)
    {
        return -1;
    }
    else if (pGood1->volumn == pGood2->volumn)
    {
        return 0;
    }
    return 1;
}

void tryBagSolution(SBag *pProblem, int step)
{
    if (step > pProblem->n)
    {
        if (pProblem->volumnLeft == 0)
        {
            printBagSolution(pProblem);
            pProblem->countOkSolution++;
        }
        return;
    }
    for (int seleted = 1; seleted >= 0; seleted--)
    {
        pProblem->nowSolution.selete[step - 1] = seleted;
        if (seleted == 1)
        {
            pProblem->volumnLeft -= pProblem->Goods[step - 1].volumn;
        }
        if (checkBagSolution(pProblem, step))
        {
            tryBagSolution(pProblem, step + 1);
        }
        /* »¹Ô­ */
        if (seleted == 1)
        {
            pProblem->volumnLeft += pProblem->Goods[step - 1].volumn;
        }
    }
}

int checkBagSolution(SBag *pProblem, int step)
{
    if (pProblem->volumnLeft < 0)
    {
        return 0;
    }
    return 1;
}

void printBagSolution(SBag *pProblem)
{
    printf("\n\t{");
    for (int i = 0; i < pProblem->n; i++)
    {
        if (pProblem->nowSolution.selete[i])
        {
            printf(" %d", pProblem->Goods[i].volumn);
        }
    }
    printf(" }");
}

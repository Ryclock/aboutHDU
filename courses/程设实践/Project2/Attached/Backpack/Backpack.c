#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Backpack.h"

void initProblem(SBag *pProblem)
{
    printf("\nPlease enter the weight limit of the backpack(10-1000): ");
    int w;
    scanf("%d", &w);
    assert(w >= 10 && w <= 1000);
    pProblem->WeightLimit = pProblem->WeightLeft = w;

    printf("\nPlease enter the item quantity(4-500): ");
    int n;
    scanf("%d", &n);
    assert(n >= 4 && n <= 500);
    pProblem->N = n;

    printf("\nPlease enter the weight and value of each item (separated by spaces):\n");
    for (int i = 0; i < pProblem->N; i++)
    {
        SGood temp;
        scanf("%d %d", &temp.Weight, &temp.Price);
        temp.pwRadio = (double)temp.Price / temp.Weight;
        pProblem->Goods[i] = temp;
        pProblem->BestSolution.SeleteA[i] = pProblem->NowSolution.SeleteA[i] = 0;
    }
    pProblem->BestSolution.MaxValue = pProblem->NowSolution.MaxValue = 0;

    qsort(pProblem->Goods, pProblem->N, sizeof(SGood), compare);
}

int compare(const void *p1, const void *p2)
{
    const SGood *pGood1 = (const SGood *)p1;
    const SGood *pGood2 = (const SGood *)p2;
    if (pGood1->pwRadio > pGood2->pwRadio)
    {
        return -1;
    }
    else if (pGood1->pwRadio == pGood2->pwRadio)
    {
        return 0;
    }
    return 1;
}

void try(SBag *pProblem, int i)
{
    if (i > pProblem->N)
    {
        if (pProblem->BestSolution.MaxValue < pProblem->NowSolution.MaxValue)
        {
            pProblem->BestSolution = pProblem->NowSolution;
        }
        return;
    }
    for (int seleted = 1; seleted >= 0; seleted--)
    {
        pProblem->NowSolution.SeleteA[i - 1] = seleted;
        if (pProblem->NowSolution.SeleteA[i - 1])
        {
            pProblem->WeightLeft -= pProblem->Goods[i - 1].Weight;
            pProblem->NowSolution.MaxValue += pProblem->Goods[i - 1].Price;
        }
        if (checkOk(pProblem, i))
        {
            try(pProblem, i + 1);
        }
        if (pProblem->NowSolution.SeleteA[i - 1])
        {
            pProblem->NowSolution.SeleteA[i - 1] = 0;
            pProblem->WeightLeft += pProblem->Goods[i - 1].Weight;
            pProblem->NowSolution.MaxValue -= pProblem->Goods[i - 1].Price;
        }
    }
}

int checkOk(SBag *pProblem, int i)
{
    if (pProblem->WeightLeft < 0)
    {
        return 0;
    }

    int maxValue = pProblem->WeightLeft * pProblem->Goods[i].pwRadio + pProblem->NowSolution.MaxValue;
    if (i + 1 < pProblem->N && maxValue <= pProblem->BestSolution.MaxValue)
    {
        return 0;
    }
    return 1;
}

void printSolution(SBag *pProblem)
{
    printf("\nMax Value is: %d", pProblem->BestSolution.MaxValue);

    int count = 0;
    for (int i = 0; i < pProblem->N; i++)
    {
        if (pProblem->BestSolution.SeleteA[i])
        {
            count++;
            printf("\nNo.%d, Weight: %d, Value: %d",
                   count, pProblem->Goods[i].Weight, pProblem->Goods[i].Price);
        }
    }
}

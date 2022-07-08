#ifndef _BACKPACK_H_INCLUDED_
#define _BACKPACK_H_INCLUDED_

#define MaxN 500

typedef struct
{
    int Weight;
    int Price;
    double pwRadio;
} SGood;

typedef struct
{
    int SeleteA[MaxN];
    int MaxValue;
} SSolution;

typedef struct
{
    int N;
    int WeightLimit, WeightLeft;
    SGood Goods[MaxN];
    SSolution BestSolution, NowSolution;
} SBag;

void initProblem(SBag *pProblem);

void printSolution(SBag *pProblem);

void try(SBag *pProblem, int i);

int checkOk(SBag *pProblem, int i);

int compare(const void *p1, const void *p2);

#endif
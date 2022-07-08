#ifndef BACKPACK_H_INCLUDED
#define BACKPACK_H_INCLUDED

#define MAXNOFBAG 50

typedef struct
{
    int volumn;
} SGood;

typedef struct
{
    int selete[MAXNOFBAG];
} SBagSolution;

typedef struct
{
    int n;
    int volumnLimit, volumnLeft;
    SGood Goods[MAXNOFBAG];
    SBagSolution nowSolution;
    int countOkSolution;
} SBag;

void backpackTest(void);

void initBagProblem(SBag *pProblem);

int compareGood(const void *p1, const void *p2);

void tryBagSolution(SBag *pProblem, int step);

int checkBagSolution(SBag *pProblem, int step);

void printBagSolution(SBag *pProblem);

#endif

#ifndef _QUEEN_H_INCLUDED_
#define _QUEEN_H_INCLUDED_

#define MAXN 20

typedef struct
{
    int checkerboard[MAXN][MAXN];
    int columnOfARow[MAXN];
} SSolution;

typedef struct
{
    int n;
    SSolution nowSolution;
    int countSolution;
} SQueen;

void initProblem(SQueen *pProblem);

void try(SQueen *pProblem, int step);

int checkOk(SQueen *pProblem, int step);

void printSolution(SQueen *pProblem);

#endif

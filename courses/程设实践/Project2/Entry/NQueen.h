#ifndef QUEEN_H_INCLUDED
#define QUEEN_H_INCLUDED

#define MAXNOFQUEEN 20

typedef struct
{
    int checkerboard[MAXNOFQUEEN][MAXNOFQUEEN];
    int columnOfARow[MAXNOFQUEEN];
} SQueenSolution;

typedef struct
{
    int n;
    SQueenSolution nowSolution;
    int countSolution;
} SQueen;

void nQueenTest(void);

void initQueenProblem(SQueen *pProblem);

void tryQueenSolution(SQueen *pProblem, int step);

int checkQueenSolution(SQueen *pProblem, int step);

void printQueenSolution(SQueen *pProblem);

#endif

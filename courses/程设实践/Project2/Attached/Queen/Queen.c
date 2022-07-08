#include <stdio.h>
#include <stdlib.h>
#include "Queen.h"

void initProblem(SQueen *pProblem)
{
    int temp;
    printf("Please input the size of checkerboard(4-20): ");
    scanf("%d", &temp);
    if (temp < 4 || temp > 20)
    {
        printf("Error!");
        system("pause");
        exit(1);
    }
    pProblem->n = temp;

    for (int i = 0; i < pProblem->n; i++)
    {
        for (int j = 0; j < pProblem->n; j++)
        {
            pProblem->nowSolution.checkerboard[i][j] = 0;
        }
        pProblem->nowSolution.columnOfARow[i] = 0;
    }
    pProblem->countSolution = 0;
}

void try(SQueen *pProblem, int step)
{
    if (step > pProblem->n)
    {
        pProblem->countSolution++;
        printSolution(pProblem);
        return;
    }

    for (int j = 0; j < pProblem->n; j++)
    {
        pProblem->nowSolution.checkerboard[step - 1][j] = 1;
        pProblem->nowSolution.columnOfARow[step - 1] = j + 1;
        if (checkOk(pProblem, step))
        {
            try(pProblem, step + 1);
        }
        pProblem->nowSolution.checkerboard[step - 1][j] = 0;
        pProblem->nowSolution.columnOfARow[step - 1] = 0;
    }
}

int checkOk(SQueen *pProblem, int step)
{
    for (int i = 1; i < step; i++)
    {
        if (pProblem->nowSolution.columnOfARow[step - 1] == pProblem->nowSolution.columnOfARow[i - 1])
        {
            return 0;
        }
        int distanceInColumn = pProblem->nowSolution.columnOfARow[i - 1] - pProblem->nowSolution.columnOfARow[step - 1];
        if ((distanceInColumn == step - i) || (distanceInColumn == i - step))
        {
            return 0;
        }
    }
    return 1;
}

void printSolution(SQueen *pProblem)
{
    printf("\n\nThe solution %d is:", pProblem->countSolution);
    for (int i = 0; i < pProblem->n; i++)
    {
        printf("\n\t");
        for (int j = 0; j < pProblem->n; j++)
        {
            printf("%d ", pProblem->nowSolution.checkerboard[i][j]);
        }
    }
}

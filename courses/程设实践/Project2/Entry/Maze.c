#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "Maze.h"

void mazeTest(void)
{
    SMaze problem, *p = &problem;
    char *fileName = "./Default.txt"; // First make sure that the path is correct
    loadMaze(p, fileName);
    printf("\nThe default maze is: ");
    printMaze(p);
    printf("\n\n\tPress Enter to choose the default maze, others to load from maze.txt: ");
    fflush(stdin);
    char ch;
    while ((ch = getchar()) != '\n')
    {
        scanf("%s", &fileName);
        loadMaze(p, fileName);
    }
    printf("\n\n\tPress Enter to show the road: ");
    fflush(stdin);
    if ((ch = getchar()) != '\n')
    {
        return;
    }
    tryMazeSolution(p);
    if (p->hasFound == 0)
    {
        printf("There is no road to the goal of this maze.");
    }
}

void loadMaze(SMaze *pProblem, char *fileName)
{
    getRowsAndCols(pProblem, fileName);
    allocMaze(pProblem);
    FILE *fp;
    fp = fopen(fileName, "r");
    assert(fp != NULL);
    for (int i = 0; i < pProblem->rows; i++)
    {
        for (int j = 0; j < pProblem->cols; j++)
        {
            int temp;
            fscanf(fp, "%d", &temp);
            switch (temp)
            {
            case 0:
                pProblem->grids[i][j].status = empty;
                break;
            case 1:
                pProblem->grids[i][j].status = wall;
                break;
            case 3:
                pProblem->grids[i][j].status = goal;
                break;
            default:
                printf("Error digit!");
                system("pause");
                break;
            }
        }
    }
    fclose(fp);
    pProblem->start.row = pProblem->start.col = 1;
    pProblem->current = pProblem->start;
    pProblem->hasFound = 0;
}

void getRowsAndCols(SMaze *pProblem, char *fileName)
{
    assert(pProblem != NULL);
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL)
    {
        perror("Error");
    }
    int cols = 0, leftRows = 0;
    char str[1024];
    fgets(str, 1024, fp);
    for (int i = 0; str[i] != '\n'; i++)
    {
        if (str[i] == ',' || str[i] == ' ')
        {
            continue;
        }
        else
        {
            cols++;
        }
    }
    pProblem->cols = cols;
    while (fgets(str, 1024, fp) != NULL)
    {
        leftRows++;
    }
    pProblem->rows = leftRows + 1;
    fclose(fp);
}

void allocMaze(SMaze *pProblem)
{
    assert(pProblem != NULL);
    pProblem->grids = (SGrid **)malloc(pProblem->rows * sizeof(SGrid *));
    for (int i = 0; i < pProblem->rows; i++)
    {
        pProblem->grids[i] = (SGrid *)malloc(pProblem->cols * sizeof(SGrid));
    }
    pProblem->start.col = pProblem->start.row = 0;
    pProblem->current = pProblem->start;
}

void tryMazeSolution(SMaze *pProblem)
{
    if (pProblem->grids[pProblem->current.row][pProblem->current.col].status == empty)
    {
        pProblem->grids[pProblem->current.row][pProblem->current.col].status = crumb;
        pProblem->current.row += 1;
        if (checkMazeSolution(pProblem))
        {
            tryMazeSolution(pProblem);
        }
        pProblem->current.row -= 1;

        pProblem->current.col += 1;
        if (checkMazeSolution(pProblem))
        {
            tryMazeSolution(pProblem);
        }
        pProblem->current.col -= 1;

        pProblem->current.col -= 1;
        if (checkMazeSolution(pProblem))
        {
            tryMazeSolution(pProblem);
        }
        pProblem->current.col += 1;

        pProblem->current.row -= 1;
        if (checkMazeSolution(pProblem))
        {
            tryMazeSolution(pProblem);
        }
        pProblem->current.row += 1;

        pProblem->grids[pProblem->current.row][pProblem->current.col].status = empty;
    }
}

int checkMazeSolution(SMaze *pProblem)
{
    if (pProblem->hasFound == 1)
    {
        return 0;
    }
    switch (pProblem->grids[pProblem->current.row][pProblem->current.col].status)
    {
    case wall:
    case crumb:
        return 0;
    case goal:
        printMaze(pProblem);
        pProblem->hasFound = 1;
    case empty:
        return 1;
    }
}

void printMaze(SMaze *pProblem)
{
    char ch;
    for (int i = 0; i < pProblem->rows; ++i)
    {
        printf("\n\t");
        for (int j = 0; j < pProblem->cols; ++j)
        {
            switch (pProblem->grids[i][j].status)
            {
            case empty:
                ch = ' ';
                break;
            case wall:
                ch = '+';
                break;
            case crumb:
                ch = 'W';
                break;
            case goal:
                ch = 'P';
                break;
            }
            printf("%c", ch);
        }
    }
    printf("\n");
}

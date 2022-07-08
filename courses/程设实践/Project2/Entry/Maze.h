#ifndef MAZE_H_INCLUDED
#define MAZE_H_INCLUDED

enum gridStatus
{
    empty,
    wall,
    crumb,
    goal
};

typedef struct
{
    int status;
} SGrid;

typedef struct
{
    int row;
    int col;
} SPoint;

typedef struct
{
    int rows, cols;
    SPoint start;
    SPoint current;
    SGrid **grids;
    int hasFound;
} SMaze;

void mazeTest(void);

void allocMaze(SMaze *pProblem);

void getRowsAndCols(SMaze *pProblem, char *fileName);

void loadMaze(SMaze *pProblem, char *fileName);

void tryMazeSolution(SMaze *pProblem);

int checkMazeSolution(SMaze *pProblem);

void printMaze(SMaze *pProblem);

#endif
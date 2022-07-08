/* Maze.h -- �Թ�����Ľӿ� */
#ifndef MAZE_H_INCLUDED
#define MAZE_H_INCLUDED

enum gridStatus
{
    empty,
    wall,
    crumb,
    entrance,
    goal
};

/* ������������ */

typedef struct SGrid SGrid;

typedef struct SPoint SPoint;

typedef struct SMaze SMaze;

/* ����ԭ�� */

void loadMaze(SMaze *pProblem, const char *fileName);

void setImportantPoints(SMaze *pProblem);

void tryMazeSolution(SMaze *pProblem);

void printMaze(const SMaze *pProblem);

#endif

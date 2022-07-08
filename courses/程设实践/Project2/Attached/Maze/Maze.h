/* Maze.h -- 迷宫问题的接口 */
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

/* 数据类型声明 */

typedef struct SGrid SGrid;

typedef struct SPoint SPoint;

typedef struct SMaze SMaze;

/* 函数原型 */

void loadMaze(SMaze *pProblem, const char *fileName);

void setImportantPoints(SMaze *pProblem);

void tryMazeSolution(SMaze *pProblem);

void printMaze(const SMaze *pProblem);

#endif

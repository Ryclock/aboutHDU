#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <stdbool.h>

#define OBSTACLE_MAX 5

typedef struct
{
    int x;
    int y;
} Obstacle;

void PrintObstacle(void);

bool IsOnObstacle(int x, int y);

#endif
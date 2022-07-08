#include "snake.h"
#include "obstacle.h"

Obstacle obstacle[OBSTACLE_MAX];

void PrintObstacle(void)
{
    for (int i = 0; i < OBSTACLE_MAX; i++)
    {
        do
        {
            obstacle[i].x = rand() % (MAP_WIDTH - 2) + 1;
            obstacle[i].y = rand() % (MAP_HEIGHT - 2) + 1;
        } while (IsOnSnake(Head, obstacle[i].x, obstacle[i].x));
        GotoXY(obstacle[i].x, obstacle[i].y);
        printf("#");
    }
}

bool IsOnObstacle(int x, int y)
{
    for (int i = 0; i < OBSTACLE_MAX; i++)
    {
        if (x == obstacle[i].x && y == obstacle[i].y)
        {
            return true;
        }
    }
    return false;
}
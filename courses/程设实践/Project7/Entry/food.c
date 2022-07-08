#include "obstacle.h"
#include "food.h"

foodType scoreToFoodType[FOODTYPE_MAX] = {
    '$',
    'A',
    'M',
    'U',
};

Food food[FOOD_MAX];

void PrintFood(void)
{
    for (int i = 0; i < FOOD_MAX; i++)
    {
        do
        {
            food[i].x = rand() % (MAP_WIDTH - 2) + 1;
            food[i].y = rand() % (MAP_HEIGHT - 2) + 1;
        } while (IsOnSnake(Head, food[i].x, food[i].y) || IsOnObstacle(food[i].x, food[i].y));
        food[i].type = rand() % FOODTYPE_MAX;
        GotoXY(food[i].x, food[i].y);
        printf("%c", scoreToFoodType[food[i].type]);
    }
}
bool EatFood(Snake *p)
{
    for (int i = 0; i < FOOD_MAX; i++)
    {
        if (p->body[0].x == food[i].x && p->body[0].y == food[i].y)
        {
            p->length++;
            p->score += food[i].type + 1;
            return true;
        }
    }
    return false;
}

void ClearFood(void)
{
    for (int i = 0; i < FOOD_MAX; i++)
    {
        if (!IsOnSnake(Head, food[i].x, food[i].y))
        {
            GotoXY(food[i].x, food[i].y);
            printf(" ");
        }
    }
}
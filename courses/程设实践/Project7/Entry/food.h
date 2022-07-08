#ifndef FOOD_H
#define FOOD_H

#include "stdbool.h"
#include "snake.h"

#define FOOD_MAX 3

typedef char foodType;
typedef struct
{
    int x;
    int y;
    Score type;
} Food;

enum foodTypeToScore
{
    $,
    A,
    M,
    U,
    FOODTYPE_MAX,
};

void PrintFood(void);

bool EatFood(Snake *p);

void ClearFood(void);
#endif
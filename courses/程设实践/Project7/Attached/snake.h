#ifndef SNAKE_H
#define SNAKE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MAP_HEIGHT 20
#define MAP_WIDTH 40
#define MAX_SNAKE_LEN 100
#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'

typedef char direction;
typedef struct Point
{
    int x;
    int y;
} Food, SnakeNode;

typedef struct
{
    SnakeNode body[MAX_SNAKE_LEN];
    int score;
    int length;
    int speed;
    direction nowForward, laterForward;
} Snake;

int PrintMenuAndGetChoice(void);

void PrintMenu(void);

int GetChoice(void);

void StartGame(void);

void PrintHelp(void);

void PrintAbout(void);

#endif
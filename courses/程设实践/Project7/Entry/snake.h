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

typedef int Score;
typedef char direction;
typedef struct
{
    int x;
    int y;
} SnakeNode;

typedef struct
{
    SnakeNode body[MAX_SNAKE_LEN];
    Score score;
    int length;
    int speed;
    direction nowForward, laterForward;
} Snake;

enum considerHeadOrNot
{
    Head,
    NoHead,
};

void GotoXY(int x, int y);

void Hide(void);

/*
    startNode: Mainly whether or not to consider the snake head
        optional value reference: value in enum considerHeadOrNot
 */
bool IsOnSnake(int startNode, int x, int y);

int PrintMenuAndGetChoice(void);

void PrintMenu(void);

int GetChoice(void);

void StartGame(void);

void PrintHelp(void);

void PrintAbout(void);

#endif
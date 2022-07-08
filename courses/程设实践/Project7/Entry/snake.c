#include <windows.h>
#include <conio.h>
#include "food.h"
#include "obstacle.h"
#include "rank.h"
#include "snake.h"

Snake snake;

/* 局部函数定义 */
void init(void);

void initMap(void);

void initSnake(void);

void printScore(void);

void moveSnake(void);

/* operate direction effectively */
bool isEffective(void);

/* direction conflict */
bool isConflict(void);

void changeHead(void);

/*
    snake.speed: sleeping delay time
    the higher score, the lower speed value
 */
void speedControl(void);

bool isDied(void);

bool isOnEdge(int x, int y);

/* 接口函数实现 */
void GotoXY(int x, int y)
{
    HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cor = {
        cor.X = x,
        cor.Y = y,
    };
    SetConsoleCursorPosition(hout, cor);
}

void Hide(void)
{
    HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO corInfo = {1, false};
    SetConsoleCursorInfo(hout, &corInfo);
}

bool IsOnSnake(int startNode, int x, int y)
{
    for (int i = startNode; i < snake.length; i++)
    {
        if (x == snake.body[i].x && y == snake.body[i].y)
        {
            return true;
        }
    }
    return false;
}

int PrintMenuAndGetChoice(void)
{
    PrintMenu();
    int result = GetChoice();
    system("cls");
    return result;
}

void PrintMenu(void)
{
    GotoXY(40, 12);
    printf("Welcome to Snake Game");
    GotoXY(43, 14);
    printf("1. Start Game");
    GotoXY(43, 16);
    printf("2. View Help");
    GotoXY(43, 18);
    printf("3. Information about us");
    GotoXY(43, 20);
    printf("Any other key to exit the game");
    Hide();
}

int GetChoice(void)
{
    char ch = _getch();
    switch (ch)
    {
    case '1':
        return 1;
    case '2':
        return 2;
    case '3':
        return 3;
    default:
        return 0;
    }
}

void StartGame(void)
{
    init();
    do
    {
        moveSnake();
    } while (!isDied());
    system("cls");
    GotoXY(45, 14);
    printf("Final Score: %d", snake.score);
    ChangeRanking(snake.score);
    GotoXY(45, 16);
    printf("You lose!");
    GotoXY(45, 18);
    printf("Any key to return to menu");
    char ch = _getch();
    system("cls");
}

void PrintHelp(void)
{
    GotoXY(20, 12);
    printf("Operation:");
    GotoXY(20, 14);
    printf("'w' UP");
    GotoXY(20, 16);
    printf("'s' DOWN");
    GotoXY(20, 18);
    printf("'a' LEFT");
    GotoXY(20, 20);
    printf("'d' RIGHT");
    GotoXY(40, 12);
    printf("Food -> Score:");
    GotoXY(40, 14);
    printf("'$' -> 1");
    GotoXY(40, 16);
    printf("'A' -> 2");
    GotoXY(40, 18);
    printf("'M' -> 3");
    GotoXY(40, 20);
    printf("'U' -> 4");
    GotoXY(60, 18);
    printf("If snake bites itself, its length will shorten");
    GotoXY(60, 20);
    printf("Game over when the snake hits a wall or an obstacle '#' ");
    GotoXY(60, 22);
    printf("Any key to return to menu");
    Hide();
    char ch = _getch();
    system("cls");
}

void PrintAbout(void)
{
    GotoXY(30, 12);
    printf("HDU - program synthesis design practice");
    GotoXY(43, 14);
    printf("Snake - Console Game");
    GotoXY(43, 16);
    printf("Any key to return to menu");
    Hide();
    char ch = _getch();
    system("cls");
}

/* 局部函数实现 */
void init(void)
{
    Hide();
    initMap();
    initSnake();
    PrintObstacle();
    PrintFood();
    printScore();
    PrintRanking();
}

void initMap(void)
{
    for (int i = 0; i < MAP_WIDTH; i++)
    {
        GotoXY(i, 0);
        printf("-");
        GotoXY(i, MAP_HEIGHT - 1);
        printf("-");
    }
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        GotoXY(0, i);
        printf("|");
        GotoXY(MAP_WIDTH - 1, i);
        printf("|");
    }
}

void initSnake(void)
{
    snake.score = 0;
    snake.length = 3;
    snake.speed = 250;
    snake.nowForward = snake.laterForward = RIGHT;
    snake.body[0].x = MAP_WIDTH / 2 - 1;
    snake.body[0].y = MAP_HEIGHT / 2 - 1;
    GotoXY(snake.body[0].x, snake.body[0].y);
    printf("@");
    for (int i = 1; i < snake.length; i++)
    {
        snake.body[i].x = snake.body[i - 1].x - 1;
        snake.body[i].y = snake.body[i - 1].y;
        GotoXY(snake.body[i].x, snake.body[i].y);
        printf("o");
    }
}

void printScore(void)
{
    GotoXY(MAP_WIDTH + 10, 5);
    printf("Current Score: %d", snake.score);
}

void moveSnake(void)
{
    SnakeNode temp = {
        .x = snake.body[snake.length - 1].x,
        .y = snake.body[snake.length - 1].y,
    };
    for (int i = snake.length - 1; i >= 1; i--)
    {
        snake.body[i].x = snake.body[i - 1].x;
        snake.body[i].y = snake.body[i - 1].y;
    }
    GotoXY(snake.body[1].x, snake.body[1].y);
    printf("o");
    if (_kbhit())
    {
        snake.laterForward = _getch();
        if (isEffective() && !isConflict())
        {
            snake.nowForward = snake.laterForward;
        }
    }
    changeHead();
    if (EatFood(&snake))
    {
        snake.body[snake.length - 1].x = temp.x;
        snake.body[snake.length - 1].y = temp.y;
        ClearFood();
        PrintFood();
        printScore();
    }
    else
    {
        GotoXY(temp.x, temp.y);
        printf(" ");
    }
    speedControl();
    Sleep(snake.speed);
    if (IsOnSnake(NoHead, snake.body[0].x, snake.body[0].y))
    {
        GotoXY(snake.body[snake.length - 1].x, snake.body[snake.length - 1].y);
        printf(" ");
        snake.length--;
    }
}

bool isEffective(void)
{
    return snake.laterForward == UP ||
           snake.laterForward == DOWN ||
           snake.laterForward == LEFT ||
           snake.laterForward == RIGHT;
}

bool isConflict(void)
{
    return (snake.laterForward == UP && snake.nowForward == DOWN) ||
           (snake.laterForward == DOWN && snake.nowForward == UP) ||
           (snake.laterForward == LEFT && snake.nowForward == RIGHT) ||
           (snake.laterForward == RIGHT && snake.nowForward == LEFT);
}

void changeHead(void)
{
    switch (snake.nowForward)
    {
    case UP:
        snake.body[0].y--;
        break;
    case DOWN:
        snake.body[0].y++;
        break;
    case LEFT:
        snake.body[0].x--;
        break;
    case RIGHT:
        snake.body[0].x++;
        break;
    }
    GotoXY(snake.body[0].x, snake.body[0].y);
    printf("@");
}

void speedControl(void)
{
    switch (snake.score)
    {
    case 5:
        snake.speed = 200;
        break;
    case 10:
        snake.speed = 180;
        break;
    case 15:
        snake.speed = 160;
        break;
    case 20:
        snake.speed = 140;
        break;
    case 25:
        snake.speed = 120;
        break;
    case 30:
        snake.speed = 100;
        break;
    case 35:
        snake.speed = 80;
        break;
    case 40:
        snake.speed = 60;
        break;
    case 45:
        snake.speed = 40;
        break;
    default:
        break;
    }
}

bool isDied(void)
{
    return IsOnObstacle(snake.body[0].x, snake.body[0].y) || isOnEdge(snake.body[0].x, snake.body[0].y);
}

bool isOnEdge(int x, int y)
{
    return x == 0 || x == MAP_WIDTH - 1 || y == 0 || y == MAP_HEIGHT - 1;
}
